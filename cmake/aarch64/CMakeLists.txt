cmake_minimum_required(VERSION 3.16)

# Set up for AArch64 cross-compilation
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Specify the cross-compilation toolchain and sysroot
set(CMAKE_SYSROOT /opt/poky/4.0.10/sysroots/cortexa65-poky-linux)
set(CMAKE_C_COMPILER /opt/poky/4.0.10/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-gcc)
set(CMAKE_CXX_COMPILER /opt/poky/4.0.10/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-g++)

# Set root path modes for cross-compilation
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Project definition
project(inferenceServer CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Proto files directory
set(PROTO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proto")
set(PROTO_FILES "${PROTO_DIR}/inference.proto")

# Output directory for generated files
set(PROTO_SRC_DIR "${PROTO_DIR}")

# Create proto directory if it doesn't exist
file(MAKE_DIRECTORY "${PROTO_SRC_DIR}")

# Generated source files
set(GENERATED_PROTO_SRCS "${PROTO_SRC_DIR}/inference.pb.cc")
set(GENERATED_PROTO_HDRS "${PROTO_SRC_DIR}/inference.pb.h")
set(GENERATED_GRPC_SRCS "${PROTO_SRC_DIR}/inference.grpc.pb.cc")
set(GENERATED_GRPC_HDRS "${PROTO_SRC_DIR}/inference.grpc.pb.h")

# Custom command to generate .pb and .grpc.pb files
add_custom_command(
    OUTPUT "${GENERATED_PROTO_SRCS}" "${GENERATED_PROTO_HDRS}" "${GENERATED_GRPC_SRCS}" "${GENERATED_GRPC_HDRS}"
    COMMAND ${CMAKE_SYSROOT}/usr/bin/protoc
    ARGS --grpc_out "${PROTO_SRC_DIR}"
         --cpp_out "${PROTO_SRC_DIR}"
         -I "${PROTO_DIR}"
         --plugin=protoc-gen-grpc=${CMAKE_SYSROOT}/usr/bin/grpc_cpp_plugin
         "${PROTO_FILES}"
    DEPENDS "${PROTO_FILES}"
    COMMENT "Generating C++ source and header files from .proto files"
)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SYSROOT}/usr/include
    ${PROTO_SRC_DIR}  # Include directory for generated .pb.h files
)

# Add executable and include the generated protobuf and gRPC sources
add_executable(${PROJECT_NAME}
    src/server.cpp
    ${GENERATED_PROTO_SRCS}
    ${GENERATED_PROTO_HDRS}
    ${GENERATED_GRPC_SRCS}
    ${GENERATED_GRPC_HDRS}
)

# Find Threads package
find_package(Threads REQUIRED)

# Link against required libraries
target_link_libraries(${PROJECT_NAME}
    ${CMAKE_SYSROOT}/usr/lib/libprotobuf.so
    ${CMAKE_SYSROOT}/usr/lib/libgrpc++.so
    ${CMAKE_SYSROOT}/usr/lib/libgrpc.so
    ${CMAKE_SYSROOT}/usr/lib/libabsl_flags.so
    ${CMAKE_SYSROOT}/usr/lib/libabsl_flags_parse.so
    ${CMAKE_SYSROOT}/usr/lib/libabsl_flags_usage.so
    ${CMAKE_SYSROOT}/usr/lib/libabsl_flags_internal.so
    ${CMAKE_SYSROOT}/usr/lib/libabsl_flags_reflection.so
    ${CMAKE_SYSROOT}/usr/lib/libabsl_flags_marshalling.so
    ${CMAKE_SYSROOT}/usr/lib/libabsl_base.so
    ${CMAKE_SYSROOT}/usr/lib/libabsl_raw_logging_internal.so
    ${CMAKE_SYSROOT}/usr/lib/libabsl_strings.so
    ${CMAKE_SYSROOT}/usr/lib/libabsl_time.so
    ${CMAKE_SYSROOT}/usr/lib/libgrpc++_reflection.so
    Threads::Threads
)

# Print debug information
message(STATUS "CMAKE_SYSROOT: ${CMAKE_SYSROOT}")
message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "PROTO_DIR: ${PROTO_DIR}")
message(STATUS "PROTO_SRC_DIR: ${PROTO_SRC_DIR}")
