cmake_minimum_required(VERSION 3.16)

project(inferenceServer CXX)

if(MSVC)
  add_definitions(-D_WIN32_WINNT=0x600)
endif()

find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)

# Find Protobuf installation
# Looks for protobuf-config.cmake file installed by Protobuf's cmake installation.
option(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
  find_program(_PROTOBUF_PROTOC protoc)
else()
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
  find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()

# Proto file
get_filename_component(inference_proto "proto/inference.proto" ABSOLUTE)
get_filename_component(inference_proto_path "${inference_proto}" PATH)

# Output directory for generated files
set(proto_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/proto")

# Generated sources
set(inference_proto_srcs "${proto_output_dir}/inference.pb.cc")
set(inference_proto_hdrs "${proto_output_dir}/inference.pb.h")
set(inference_grpc_srcs "${proto_output_dir}/inference.grpc.pb.cc")
set(inference_grpc_hdrs "${proto_output_dir}/inference.grpc.pb.h")

# Create proto directory if it doesn't exist
file(MAKE_DIRECTORY "${proto_output_dir}")

# Custom command to generate protobuf and gRPC files
add_custom_command(
  OUTPUT "${inference_proto_srcs}" "${inference_proto_hdrs}" "${inference_grpc_srcs}" "${inference_grpc_hdrs}"
  COMMAND ${_PROTOBUF_PROTOC}
  ARGS --grpc_out "${proto_output_dir}"
       --cpp_out "${proto_output_dir}"
       -I "${inference_proto_path}"
       --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
       "${inference_proto}"
  DEPENDS "${inference_proto}"
  COMMENT "Generating protobuf and gRPC source files")

# Include generated *.pb.h files
include_directories("${proto_output_dir}")

# inference_grpc_proto library
add_library(inference_grpc_proto
  ${inference_grpc_srcs}
  ${inference_grpc_hdrs}
  ${inference_proto_srcs}
  ${inference_proto_hdrs})
target_link_libraries(inference_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Server executable
add_executable(server "src/server.cpp")
target_link_libraries(server
  inference_grpc_proto
  absl::flags
  absl::flags_parse
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Client executable
add_executable(client "src/client.cpp" "src/frame_rate_logger.h" "src/frame_rate_logger.cpp")
target_link_libraries(client
  inference_grpc_proto
  absl::flags
  absl::flags_parse
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF}
  ${OpenCV_LIBS}
)

target_include_directories(client PUBLIC ${OpenCV_INCLUDE_DIRS} ${proto_output_dir})

# Debug information
message(STATUS "Proto output directory: ${proto_output_dir}")
