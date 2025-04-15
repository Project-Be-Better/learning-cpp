cmake_minimum_required(VERSION 3.15)
project(day09_memory_lifetime VERSION 1.0.0 LANGUAGES CXX)

# Set modern C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configure build type (Debug by default)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Set output directories to keep all artifacts in the build folder
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find the Conan-generated files
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/Release/generators)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/Release/generators)

# Conan setup
if(EXISTS "${CMAKE_BINARY_DIR}/Release/generators/conan_toolchain.cmake")
    include("${CMAKE_BINARY_DIR}/Release/generators/conan_toolchain.cmake")
endif()

# Set direct paths to GTest libraries and includes
set(GTEST_INCLUDE_DIR "/home/thommankutty/.conan2/p/b/gtestacd67e6db34e1/p/include")
set(GTEST_LIBRARY "/home/thommankutty/.conan2/p/b/gtestacd67e6db34e1/p/lib/libgtest.a")
set(GTEST_MAIN_LIBRARY "/home/thommankutty/.conan2/p/b/gtestacd67e6db34e1/p/lib/libgtest_main.a")

# Include directories
include_directories(include)
include_directories(${GTEST_INCLUDE_DIR})

# Create library target
add_library(lifecycle src/RawPointer.cpp)

# Create main executable
add_executable(pointer_demo src/main.cpp)
target_link_libraries(pointer_demo PRIVATE lifecycle)

# Testing setup
enable_testing()

# Create test executable with direct linking to GTest libraries
add_executable(test_runner test/test_RawPointer.cpp)
target_link_libraries(test_runner PRIVATE
    ${GTEST_MAIN_LIBRARY}
    ${GTEST_LIBRARY}
    lifecycle
    pthread  # GTest requires pthread on Linux
)

# Add test to CTest
add_test(NAME test_runner COMMAND test_runner)