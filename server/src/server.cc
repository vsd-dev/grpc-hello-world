#include <iostream>
#include <grpcpp/grpcpp.h>
#include "proto/hello.grpc.pb.h"
#include "proto/hello.pb.h"
#include <opencv2/opencv.hpp>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

// Namespace defined in your .proto file, if you added 'package processing;'
using processing::Numeric;
using processing::Point3;
using processing::ImageRequest;
using processing::ImageResponse;
using processing::ProcessingServices; // If you have a package 'processing' in the .proto file

// Helper function to convert bytes to OpenCV Mat
cv::Mat BytesToMat(const std::string& bytes) {
    std::vector<uchar> data(bytes.begin(), bytes.end());
    return cv::imdecode(data, cv::IMREAD_COLOR);
}

// Helper function to convert OpenCV Mat to bytes
std::string MatToBytes(const cv::Mat& mat) {
    std::vector<uchar> buf;
    cv::imencode(".jpg", mat, buf);
    return std::string(buf.begin(), buf.end());
}

// Define a class that implements the ProcessingServices service
class ProcessingImpl : public ProcessingServices::Service
{
public:
  // Implementation of the computeSum RPC method
  Status computeSum(ServerContext *context, const Point3 *request, Numeric *response) override
  {
    std::cout << "Called computeSum with: ("
              << request->x() << ", "
              << request->y() << ", "
              << request->z() << ")" << std::endl;
    // Calculate the sum of x, y, and z from the request message
    response->set_value(request->x() + request->y() + request->z());
    return Status::OK;
  }
  // Implementation of the resizeImage RPC method
  Status resizeImage(ServerContext *context, const ImageRequest *request, ImageResponse *response) override
  {
    std::cout << "Called resizeImage " << std::endl;
    cv::Mat img = BytesToMat(request->image_data());
    if (img.empty()) {
      return Status(grpc::INVALID_ARGUMENT, "Invalid image data");
    }
    // Resize Image
    cv::Mat resized_img;
    cv::resize(img, resized_img, cv::Size(100, 100));// TODO parameterize target width, target height

    // Convert OpenCV Mat back to bytes and set response
    std::string resized_img_bytes = MatToBytes(resized_img);
    response->set_resized_image_data(resized_img_bytes);
    return Status::OK;
  }
};
int main()
{
  // Create an instance of the service implementation
  ProcessingImpl service;
  // Define the server address and port
  grpc::ServerBuilder builder;
  builder.AddListeningPort("0.0.0.0:9999", grpc::InsecureServerCredentials());
  // Register the service with the server
  builder.RegisterService(&service);
  // Build and start the server
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on 0.0.0.0:9999" << std::endl;
  // Wait for the server to shut down
  server->Wait();
  return 0;
}
