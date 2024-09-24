#include <iostream>
#include <grpcpp/grpcpp.h>
#include "proto/hello.grpc.pb.h"
#include "proto/hello.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

// Namespace defined in your .proto file, if you added 'package processing;'
using processing::ProcessingServices;  // If you have a package 'processing' in the .proto file
using processing::Point3;
using processing::Numeric;

// Define a class that implements the ProcessingServices service
class ProcessingImpl : public ProcessingServices::Service {
 public:
  // Implementation of the computeSum RPC method
  Status computeSum(ServerContext* context, const Point3* request, Numeric* response) override {
    std::cout << "Called computeSum with: (" 
              << request->x() << ", " 
              << request->y() << ", " 
              << request->z() << ")" << std::endl;
    // Calculate the sum of x, y, and z from the request message
    response->set_value(request->x() + request->y() + request->z());
    return Status::OK;
  }
};
int main() {
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

