cmake_minimum_required(VERSION 3.14)

project(
  # Project name
  build-with-cmake

  # Project language CXX is CPP
  LANGUAGES CXX
  # Project version
  VERSION 0.1.0
)

# Explicitly set CPP standard to C++17
set(CMAKE_CXX_STANDARD 17)

# https://stackoverflow.com/questions/9345792/cmake-executable-location
# set desired output location of our executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(./source)
