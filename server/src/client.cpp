#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "proto/hello.grpc.pb.h"
#include "proto/hello.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using processing::ProcessingServices;  // Use the namespace 'processing' if defined in proto
using processing::Point3;
using processing::Numeric;

// Define a client class that interacts with the ProcessingServices service
class ProcessingClient {
 public:
  // Constructor: Creates a new stub for the ProcessingServices service
  ProcessingClient(std::shared_ptr<Channel> channel)
      : stub_(ProcessingServices::NewStub(channel)) {}

  // Calls the computeSum method on the server
  float ComputeSum(float x, float y, float z) {
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
    if (status.ok()) {
      return response.value();
    } else {
      std::cout << "RPC failed" << std::endl;
      return -1.0f;
    }
  }

 private:
  // Stub for making calls to the server
  std::unique_ptr<ProcessingServices::Stub> stub_;
};

int main(int argc, char** argv) {
  // Create a new client and connect to the server
  ProcessingClient client(grpc::CreateChannel("localhost:9999", grpc::InsecureChannelCredentials()));
  // Call the ComputeSum method with sample data
  float x = 3.0f;
  float y = 4.0f;
  float z = 6.0f;
  float result = client.ComputeSum(x, y, z);
  // Output the result
  std::cout << "Sum of (" << x << ", " << y << ", " << z << ") is: " << result << std::endl;
  return 0;
}
