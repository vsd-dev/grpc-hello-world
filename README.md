
# gRPC Example: Simple Sum and Image Processing Service in C++

This repository contains a gRPC service and client implementation in C++. The service, `ProcessingServices`, provides two methods: `computeSum` for calculating the sum of three floating-point numbers, and `resizeImage` for resizing an image using OpenCV. The client can specify which operation to perform via command-line arguments.

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
- [Usage](#usage)
  - [Compute Sum](#compute-sum)
  - [Resize Image](#resize-image)
- [License](#license)

## Introduction

This project demonstrates a gRPC client-server communication setup using C++ for multiple operations. It includes:

- Defining a gRPC service with methods for computing sums and resizing images.
- Implementing a gRPC server that provides these services.
- Implementing a gRPC client that can perform these operations based on command-line arguments.

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

Ensure you have the following installed on your system:

- CMake 3.16 or higher
- gRPC and Protocol Buffers libraries
- OpenCV library for image processing
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

   Open another terminal in the `build` directory and run one of the following commands:

   **Compute Sum:**

   ```bash
   ./client --computeSum 3.0 4.0 6.0
   ```

   **Resize Image:**

   ```bash
   ./client --resizeImage input.jpg resized_output.jpg
   ```

   In the above command, replace `input.jpg` with your input image file path and `resized_output.jpg` with the desired output image file path.

## Code Walkthrough

### hello.proto

The `.proto` file defines the `ProcessingServices` service with two RPC methods:

- **`computeSum`**: Accepts three float values in a `Point3` message and returns their sum in a `Numeric` message.
- **`resizeImage`**: Accepts an image in bytes and returns the resized image in bytes.

### Server Implementation

The server implements both methods defined in the `.proto` file. It listens for incoming client requests on `0.0.0.0:9999`. When the `computeSum` method is called, it calculates the sum of the `x`, `y`, and `z` fields from the `Point3` message. When the `resizeImage` method is called, it resizes the image to 100x100 pixels and returns the resized image.

### Client Implementation

The client uses command-line arguments to specify the operation. It connects to the gRPC server and either:

- Calls the `computeSum` method with three float values.
- Sends an image file to the `resizeImage` method and saves the resized image.

## Usage

### Compute Sum

To calculate the sum of three numbers, run:

```bash
./client --computeSum x y z
```

For example:

```bash
./client --computeSum 3.0 4.0 6.0
```

### Resize Image

To resize an image, run:

```bash
./client --resizeImage input_image_path output_image_path
```

For example:

```bash
./client --resizeImage input.jpg resized_output.jpg
```

Ensure that `input.jpg` is a valid image file in the current directory.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
