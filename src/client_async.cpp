#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>
#include <grpcpp/grpcpp.h>
#include <grpcpp/alarm.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <opencv2/opencv.hpp>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include "inference.grpc.pb.h"
#include "frame_rate_logger.h"
#include "answer_to_everything.h"

ABSL_FLAG(std::string, serverAddress, "10.0.0.91:50051", "Server address");
ABSL_FLAG(int, batchSize, 48, "The batch size");
ABSL_FLAG(int, imageWidth, 256, "The image width");
ABSL_FLAG(int, imageHeight, 256, "The image height");
ABSL_FLAG(int, imageChannels, 1, "The amount of image channels");
ABSL_FLAG(int, runBatchCount, 10000, "The number of batches to process");
ABSL_FLAG(int, loggingFrequency, 1, "The logging frequency (seconds)");
ABSL_FLAG(std::string, imageFolder, "/home/vishnu/Downloads/GRPC/inference_server/test_Images/test1", "Folder containing the images");

using grpc::Channel;
using grpc::ClientAsyncReaderWriter;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

class AsyncClient
{
public:
    AsyncClient(std::shared_ptr<Channel> channel)
        : stub_(inference::InferenceService::NewStub(channel)) {}

    void Start(const std::string &imageFolder, int batchSize, int imageWidth, int imageHeight, int imageChannels, int runBatchCount, int loggingFrequency)
    {
        batchSize_ = batchSize;
        imageWidth_ = imageWidth;
        imageHeight_ = imageHeight;
        imageChannels_ = imageChannels;
        runBatchCount_ = runBatchCount; // Replace runtimeInSeconds with runBatchCount

        // Initialize FrameRateLogger with loggingFrequency, batchSize, and buffer size
        frameRateLogger_ = std::make_unique<FrameRateLogger>(loggingFrequency, batchSize, 5); // Check averageCount parameter as needed

        // Prepare batch images
        std::vector<unsigned char> batch_image_bytes;
        for (int i = 0; i < batchSize; ++i)
        {
            std::string image_path = imageFolder + "/VR014_N001400.bmp";
            std::vector<unsigned char> image_bytes = ReadAndPreprocessImage(image_path, imageWidth, imageHeight, imageChannels);
            batch_image_bytes.insert(batch_image_bytes.end(), image_bytes.begin(), image_bytes.end());
        }

        request_.set_batch_size(batchSize_);
        request_.set_image_height(imageHeight_);
        request_.set_image_width(imageWidth_);
        request_.set_image_channels(imageChannels_);
        request_.set_image_data(reinterpret_cast<char *>(batch_image_bytes.data()), batch_image_bytes.size());

        // Print the total size of the concatenated image bytes
        std::cout << "Total size of concatenated image bytes: " << batch_image_bytes.size() << " bytes" << std::endl;

        // Create the gRPC context and stream
        context_ = std::make_unique<ClientContext>();
        stream_ = stub_->AsyncPredictBatchAsync(context_.get(), &cq_, (void *)1); // Call AsyncPredictBatchAsync

        // Start handling gRPC events in a separate thread
        processing_thread_ = std::thread(&AsyncClient::HandleEvents, this);
    }

    ~AsyncClient()
    {
        if (processing_thread_.joinable())
        {
            processing_thread_.join();
        }
    }

private:
    std::unique_ptr<inference::InferenceService::Stub> stub_;
    std::unique_ptr<ClientContext> context_;
    std::unique_ptr<ClientAsyncReaderWriter<inference::Request, inference::Response>> stream_;
    CompletionQueue cq_; // Use a raw CompletionQueue object here
    inference::Request request_;
    inference::Response response_;
    std::vector<unsigned char> batch_image_bytes_;
    std::thread processing_thread_;
    std::unique_ptr<FrameRateLogger> frameRateLogger_; // Add a pointer to the FrameRateLogger
    int batchSize_, imageWidth_, imageHeight_, imageChannels_, runBatchCount_; // Use runBatchCount_
    std::atomic<int> batchIndex_{0};
    std::atomic<bool> write_in_progress_{false}; // Track ongoing write operation
    std::atomic<bool> read_in_progress_{false};  // Track ongoing read operation
    Status status_;

    // Function to read and preprocess an image
    std::vector<unsigned char> ReadAndPreprocessImage(const std::string &image_path, int imageWidth, int imageHeight, int imageChannels)
    {
        cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR); // Read image in color
        if (img.empty())
        {
            std::cerr << "Failed to read image from: " << image_path << std::endl;
            throw std::runtime_error("Failed to read image");
        }

        // Resize image to the specified width and height
        cv::resize(img, img, cv::Size(imageWidth, imageHeight));

        // Convert to grayscale if required
        if (imageChannels == 1)
        {
            cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
        }

        // Convert image to raw bytes
        std::vector<unsigned char> image_bytes;
        if (imageChannels == 1)
        {
            image_bytes.assign(img.data, img.data + imageWidth * imageHeight);
        }
        else
        {
            image_bytes.assign(img.data, img.data + imageWidth * imageHeight * imageChannels);
        }

        return image_bytes;
    }

    // Method to handle events from the completion queue
    void HandleEvents()
    {
        void *got_tag;
        bool ok;
        while (cq_.Next(&got_tag, &ok))
        { // Using raw CompletionQueue object here
            if (!ok)
            {
                std::cerr << "Event not ok. Tag: " << got_tag << std::endl;
                break;
            }

            if (got_tag == (void *)1)
            { // Stream created
                std::cout << "Stream created successfully." << std::endl;
                InitiateWrite(); // Start the first write operation
            }
            else if (got_tag == (void *)2)
            { // Write done
                write_in_progress_ = false; // Mark write as complete
                if (!read_in_progress_)
                {
                    InitiateRead(); // Start read if not in progress
                }
            }
            else if (got_tag == (void *)3)
            { // Read done
                read_in_progress_ = false; // Mark read as complete
                // Call FrameRateLogger to log the current write-read cycle
                OnReadDone(); // Process the read response
                batchIndex_++;
                if (batchIndex_ < runBatchCount_ && !write_in_progress_)
                {
                    InitiateWrite(); // Continue writing next request
                }
                else if (batchIndex_ >= runBatchCount_)
                {
                    std::cout << "No more requests to send. Calling WritesDone." << std::endl;
                    stream_->WritesDone((void *)4); // Complete writing
                }
            }
            else if (got_tag == (void *)4)
            { // WritesDone done
                std::cout << "WritesDone completed." << std::endl;
                stream_->Finish(&status_, (void *)5); // Finish the stream
            }
            else if (got_tag == (void *)5)
            { // Stream finished
                if (status_.ok())
                {
                    std::cout << "Stream finished successfully." << std::endl;
                }
                else
                {
                    std::cerr << "Stream finished with error: " << status_.error_message() << std::endl;
                }
                break; // Exit the loop once the stream is finished
            }
        }
    }

    // Initiates a write operation if not already in progress
    void InitiateWrite()
    {
        if (!write_in_progress_)
        {
            request_.set_batch_index(batchIndex_); // Set batch index before sending request
            write_in_progress_ = true;
            stream_->Write(request_, (void *)2);
        }
        else
        {
            std::cerr << "Write already in progress!" << std::endl;
        }
    }

    // Initiates a read operation if not already in progress
    void InitiateRead()
    {
        if (!read_in_progress_)
        {
            read_in_progress_ = true;
            stream_->Read(&response_, (void *)3);
        }
        else
        {
            std::cerr << "Read already in progress!" << std::endl;
        }
    }

    // Method to process the read response
    void OnReadDone()
    {
        std::vector<int> classification;
        int size = response_.classification_size();
        for (int i = 0; i < size; i++)
        {
            int classification_out = response_.classification(i);
            classification.push_back(response_.classification(i));
        }

        // Check response
        if (classification.size() == 0 || classification[0] != ANSWER_TO_EVERYTHING)
        {
            throw std::runtime_error("WRONG RESPONSE");
        }
        frameRateLogger_->run("Write-read");
    }
};

int main(int argc, char **argv)
{
    absl::ParseCommandLine(argc, argv);
    std::string serverAddress = absl::GetFlag(FLAGS_serverAddress);
    int batchSize = absl::GetFlag(FLAGS_batchSize);
    int imageWidth = absl::GetFlag(FLAGS_imageWidth);
    int imageHeight = absl::GetFlag(FLAGS_imageHeight);
    int imageChannels = absl::GetFlag(FLAGS_imageChannels);
    int runBatchCount = absl::GetFlag(FLAGS_runBatchCount); // Replaced runtimeInSeconds with runBatchCount
    int loggingFrequency = absl::GetFlag(FLAGS_loggingFrequency);
    std::string imageFolder = absl::GetFlag(FLAGS_imageFolder);

    AsyncClient client(grpc::CreateChannel(serverAddress, grpc::InsecureChannelCredentials()));
    client.Start(imageFolder, batchSize, imageWidth, imageHeight, imageChannels, runBatchCount, loggingFrequency);

    return 0;
}
