#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <grpcpp/grpcpp.h>
#include <opencv2/opencv.hpp>
#include "proto/hello.grpc.pb.h"
#include "proto/hello.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using processing::ImageRequest;
using processing::ImageResponse;
using processing::Numeric;
using processing::Point3;
using processing::ProcessingServices; // Use the namespace 'processing' if defined in proto

// Helper function to read image from file and convert to bytes
std::string ReadImageAsBytes(const std::string& image_path) {
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Could not read the image: " << image_path << std::endl;
        return "";
    }
    std::vector<uchar> buf;
    cv::imencode(".jpg", img, buf);
    return std::string(buf.begin(), buf.end());
}

// Helper function to save bytes as image file
void SaveBytesAsImage(const std::string& bytes, const std::string& output_path) {
    std::vector<uchar> data(bytes.begin(), bytes.end());
    cv::Mat img = cv::imdecode(data, cv::IMREAD_COLOR);
    cv::imwrite(output_path, img);
}

// Define a client class that interacts with the ProcessingServices service
class ProcessingClient
{
public:
  // Constructor: Creates a new stub for the ProcessingServices service
  ProcessingClient(std::shared_ptr<Channel> channel)
      : stub_(ProcessingServices::NewStub(channel)) {}

  // Calls the computeSum method on the server
  float ComputeSum(float x, float y, float z)
  {
    // Create a request message
    Point3 request;
    request.set_x(x);
    request.set_y(y);
    request.set_z(z);

    // Container for the data we expect from the server
    Numeric response;
    // Context for the client, it could be used to convey extra information to the server
    ClientContext context;
    // Call the remote computeSum method
    Status status = stub_->computeSum(&context, request, &response);
    // Act upon its status
    if (status.ok())
    {
      return response.value();
    }
    else
    {
      std::cout << "RPC failed" << std::endl;
      return -1.0f;
    }
  }

  // Calls the computeSum method on the server
  void SendImageAndReceiveResized(const std::string image_path, const std::string& output_path)
  {
    // Create a request message
    ImageRequest request;
    request.set_image_data(ReadImageAsBytes(image_path));
    if (request.image_data().empty()) {
        std::cerr << "Failed to read image data." << std::endl;
        return;
    }
    // Container for the data we expect from the server
    ImageResponse response;
    // Context for the client, it could be used to convey extra information to the server
    ClientContext context;
    // Call the remote computeSum method
    Status status = stub_->resizeImage(&context, request, &response);
    // Act upon its status
    if (status.ok())
    {
      SaveBytesAsImage(response.resized_image_data(), output_path);
    }
    else
    {
      std::cerr << "RPC failed: " << status.error_message() << std::endl;
    }
  }

private:
  // Stub for making calls to the server
  std::unique_ptr<ProcessingServices::Stub> stub_;
};

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [--computeSum x y z | --resizeImage input_image output_image]" << std::endl;
        return 1;
    }

    ProcessingClient client(grpc::CreateChannel("localhost:9999", grpc::InsecureChannelCredentials()));

    // Check the first argument to determine which method to call
    std::string command = argv[1];
    if (command == "--computeSum") {
        if (argc != 5) {
            std::cerr << "Usage for computeSum: " << argv[0] << " --computeSum x y z" << std::endl;
            return 1;
        }
        float x = std::stof(argv[2]);
        float y = std::stof(argv[3]);
        float z = std::stof(argv[4]);
        float result = client.ComputeSum(x, y, z);
        std::cout << "Sum of (" << x << ", " << y << ", " << z << ") is: " << result << std::endl;
    } 
    else if (command == "--resizeImage") {
        if (argc != 4) {
            std::cerr << "Usage for resizeImage: " << argv[0] << " --resizeImage input_image output_image" << std::endl;
            return 1;
        }
        std::string input_image = argv[2];
        std::string output_image = argv[3];
        client.SendImageAndReceiveResized(input_image, output_image);
    } 
    else {
        std::cerr << "Invalid command. Usage: " << argv[0] << " [--computeSum x y z | --resizeImage input_image output_image]" << std::endl;
        return 1;
    }

    return 0;
}