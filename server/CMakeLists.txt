cmake_minimum_required(VERSION 3.16)
project(myserver)

# Set the compile commands export option
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find necessary packages
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# Add a library target for the proto files
add_library(protolib proto/hello.proto)
target_link_libraries(protolib gRPC::grpc++)
target_include_directories(protolib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Get the location of the gRPC C++ plugin
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)

# Generate protobuf and gRPC files
protobuf_generate(
    TARGET protolib 
    LANGUAGE cpp
)
protobuf_generate(
    TARGET protolib 
    LANGUAGE grpc 
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc 
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
)

# Add the server executable and link it with the necessary libraries
add_executable(server src/server.cc)
target_link_libraries(server protolib gRPC::grpc++)

# Add the client executable and link it with the necessary libraries
add_executable(client src/client.cpp)  # Add client.cpp to the project
target_link_libraries(client protolib gRPC::grpc++)  # Link client with protolib and gRPC libraries

# Include the directory where protobuf and gRPC files are generated
target_include_directories(client PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(server PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
