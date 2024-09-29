#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include <grpcpp/grpcpp.h>

#include "inference.grpc.pb.h"

#include "frame_rate_logger.h"
#include "answer_to_everything.h"

#include <opencv2/opencv.hpp>

ABSL_FLAG(std::string, serverAddress, "10.0.0.91:50051", "Server address");
ABSL_FLAG(int, batchSize, 48, "The batch size");
ABSL_FLAG(int, imageWidth, 256, "The image width");
ABSL_FLAG(int, imageHeight, 256, "The image height");
ABSL_FLAG(int, imageChannels, 1, "The amount of image channels");
ABSL_FLAG(int, runBatchCount, 10000, "The number of batches to process");
ABSL_FLAG(int, loggingFrequency, 1, "The logging frequency (seconds)");
ABSL_FLAG(std::string, imageFolder, "/home/vishnu/Downloads/GRPC/inference_server/test_Images/test1", "Folder containing the images");

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

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

int main(int argc, char **argv)
{
    // Read flags
    absl::ParseCommandLine(argc, argv);
    std::string serverAddress = absl::GetFlag(FLAGS_serverAddress);
    int batchSize = absl::GetFlag(FLAGS_batchSize);
    int imageWidth = absl::GetFlag(FLAGS_imageWidth);
    int imageHeight = absl::GetFlag(FLAGS_imageHeight);
    int imageChannels = absl::GetFlag(FLAGS_imageChannels);
    int runBatchCount = absl::GetFlag(FLAGS_runBatchCount);  // Replace runtimeInSeconds with runBatchCount
    int loggingFrequency = absl::GetFlag(FLAGS_loggingFrequency);
    std::string imageFolder = absl::GetFlag(FLAGS_imageFolder);

    std::unique_ptr<inference::InferenceService::Stub> stub = inference::InferenceService::NewStub(grpc::CreateChannel(serverAddress, grpc::InsecureChannelCredentials()));
    ClientContext context;
    std::shared_ptr<grpc::ClientReaderWriter<inference::Request, inference::Response>> stream(stub->PredictBatch(&context));

    // Read and concatenate image bytes
    std::vector<unsigned char> batch_image_bytes;
    for (int i = 0; i < batchSize; ++i)
    {
        // Assuming only one image in the folder and using it repeatedly to create the batch
        std::string image_path = imageFolder + "/VR014_N001400.bmp";
        std::vector<unsigned char> image_bytes = ReadAndPreprocessImage(image_path, imageWidth, imageHeight, imageChannels);
        batch_image_bytes.insert(batch_image_bytes.end(), image_bytes.begin(), image_bytes.end());
    }

    // Print the total size of the concatenated image bytes
    std::cout << "Total size of concatenated image bytes: " << batch_image_bytes.size() << " bytes" << std::endl;

    inference::Request request;
    request.set_batch_size(batchSize);
    request.set_image_height(imageHeight);
    request.set_image_width(imageWidth);
    request.set_image_channels(imageChannels);
    request.set_image_data(reinterpret_cast<char *>(batch_image_bytes.data()), batch_image_bytes.size());

    int batchIndex = 0;
    FrameRateLogger frameRateLogger(loggingFrequency, batchSize, 5);

    while (batchIndex < runBatchCount)
    {
        // Write stream
        request.set_batch_index(batchIndex);
        if (!stream->Write(request))
        {
            std::cout << "Broken write stream" << std::endl;
            break;
        }

        // Read stream
        inference::Response response;
        if (!stream->Read(&response))
        {
            std::cout << "Broken read stream" << std::endl;
            break;
        }

        // Read response
        std::vector<int> classification;
        int size = response.classification_size();
        for (int i = 0; i < size; i++)
        {
            classification.push_back(response.classification(i));
        }

        // Check response
        if (classification.size() == 0 || classification[0] != ANSWER_TO_EVERYTHING)
        {
            throw std::runtime_error("WRONG RESPONSE");
        }

        // Increase written batch index
        batchIndex++;

        // Run logger
        frameRateLogger.run("Write-read");
    }

    stream->WritesDone();
    Status status = stream->Finish();
    if (status.ok())
    {
        std::cout << "Finished stream" << std::endl;
    }
    else
    {
        std::cout << "Finishing stream failed" << std::endl;
    }

    // Shutting down server
    ClientContext shutdownContext;
    inference::Empty response;
    status = stub->ShutdownServer(&shutdownContext, inference::Empty(), &response);

    if (!status.ok())
    {
        std::cout << "Shutdown server failed" << std::endl;
    }

    return 0;
}
