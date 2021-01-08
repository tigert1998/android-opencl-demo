cmake_minimum_required (VERSION 3.12)

project("Android OpenCL Demo" LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(3rd_party/libopencl-stub)

set(THIRD_PARTY_ROOT_PATH "${PROJECT_SOURCE_DIR}/3rd_party")
set(SRC_ROOT_PATH "${PROJECT_SOURCE_DIR}/android-opencl-demo")

add_executable(
    "main"
    "${SRC_ROOT_PATH}/main.cc"
)

target_include_directories(
    "main" PUBLIC
    "${THIRD_PARTY_ROOT_PATH}/libopencl-stub/include"
)

target_compile_definitions("main" PUBLIC CL_TARGET_OPENCL_VERSION=200)
target_compile_definitions("main" PRIVATE USE_STUB_OPENCL)
target_compile_options("main" PRIVATE -fPIC -O2 -fexceptions)
target_link_libraries("main" OpenCL)