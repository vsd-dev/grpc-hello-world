
# gRPC Example: Simple Sum Service in C++

This repository contains a basic implementation of a gRPC service and client in C++. The service, `ProcessingServices`, provides a method called `computeSum` that calculates the sum of three floating-point numbers. The client sends three values to the server and receives the sum in response.

## Table of Contents

- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Building the Project](#building-the-project)
  - [Running the Server and Client](#running-the-server-and-client)
- [Code Walkthrough](#code-walkthrough)
  - [hello.proto](#helloproto)
  - [Server Implementation](#server-implementation)
  - [Client Implementation](#client-implementation)
- [License](#license)

## Introduction

This project demonstrates a simple gRPC client-server communication setup using C++. It covers the following:

- Defining a gRPC service and messages in a `.proto` file.
- Implementing a gRPC server that provides the service.
- Implementing a gRPC client that calls the service.

## Project Structure

```
.
├── CMakeLists.txt          # CMake build configuration file
├── README.md               # Project documentation
├── proto
│   └── hello.proto         # gRPC service definition
├── server.cc               # Server-side implementation
└── client.cpp              # Client-side implementation
```

## Getting Started

### Prerequisites

Make sure you have the following installed on your system:

- CMake 3.16 or higher
- gRPC and Protocol Buffers libraries
- C++ Compiler (g++ or clang)
- `protoc` (Protocol Buffers compiler)

### Installing gRPC
- `git clone --recurse-submodules -b v1.62.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc`
- `mkdir -p grpc/build && cd grpc/build`
- `cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF ..`
- `make -j8 install`
### Building the Project

1. **Clone the Repository:**

   ```bash
   git clone <your-repo-url>
   cd <repo-name>
   ```

2. **Generate the gRPC and Protocol Buffer Code:**

   Navigate to the root directory of the project and run:

   ```bash
   protoc -I=proto --grpc_out=proto --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` proto/hello.proto
   protoc -I=proto --cpp_out=proto proto/hello.proto
   ```

3. **Build the Server and Client:**

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

### Running the Server and Client

1. **Run the Server:**

   Start the gRPC server by executing the following command in the `build` directory:

   ```bash
   ./server
   ```

2. **Run the Client:**

   Open another terminal in the `build` directory and run:

   ```bash
   ./client
   ```

   You should see the output:

   ```
   Sum of (3, 4, 6) is: 13
   ```

## Code Walkthrough

### hello.proto

This file defines the `ProcessingServices` service with a single RPC method, `computeSum`, that takes a `Point3` message and returns a `Numeric` message.

- **Point3:** Represents a 3D point with `x`, `y`, and `z` coordinates.
- **Numeric:** Represents a single floating-point value, which is the sum of the coordinates.
- **computeSum:** An RPC method that computes the sum of the coordinates of a `Point3` message.

### Server Implementation

The server implements the `ProcessingServices` service defined in the `.proto` file. It listens for incoming client requests on `0.0.0.0:9999`. When the `computeSum` method is called, it calculates the sum of the `x`, `y`, and `z` fields from the `Point3` message and returns the result.

### Client Implementation

The client connects to the gRPC server and calls the `computeSum` method. It sends a `Point3` message containing three values (`x`, `y`, and `z`) and receives the computed sum in response. This showcases how easy it is to perform remote procedure calls using gRPC.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
