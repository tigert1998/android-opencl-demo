cmake_minimum_required (VERSION 3.12)

project("Android OpenCL Demo" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS OFF)
add_subdirectory(3rd_party/OpenCL-SDK)

set(THIRD_PARTY_ROOT_PATH "${PROJECT_SOURCE_DIR}/3rd_party")
set(SRC_ROOT_PATH "${PROJECT_SOURCE_DIR}/android-opencl-demo")

set(OpenCL_INCLUDE_DIR "${THIRD_PARTY_ROOT_PATH}/OpenCL-SDK/external/OpenCL-Headers")

add_executable(
    "main"
    "${SRC_ROOT_PATH}/main.cc"
)

include_directories(${OpenCL_INCLUDE_DIR})

target_compile_definitions("main" PUBLIC CL_TARGET_OPENCL_VERSION=200)
target_link_libraries("main" OpenCL)