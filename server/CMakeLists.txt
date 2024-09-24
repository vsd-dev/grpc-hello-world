cmake_minimum_required(VERSION 3.16)
project(grpc_image_example)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(OpenCV REQUIRED)

add_library(proto_lib proto/hello.proto)
target_link_libraries(proto_lib gRPC::grpc++)
target_include_directories(proto_lib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET proto_lib LANGUAGE cpp)
protobuf_generate(TARGET proto_lib LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")

# Server
add_executable(server src/server.cc)
target_link_libraries(server proto_lib gRPC::grpc++ ${OpenCV_LIBS})
target_include_directories(server PUBLIC ${OpenCV_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

# Client
add_executable(client src/client.cpp)
target_link_libraries(client proto_lib gRPC::grpc++ ${OpenCV_LIBS})
target_include_directories(client PUBLIC ${OpenCV_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})