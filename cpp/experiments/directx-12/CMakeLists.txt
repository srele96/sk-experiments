cmake_minimum_required(VERSION 3.10)

project(
  directx-12
  LANGUAGES CXX
  VERSION 0.1.0
)

set(CMAKE_C_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(./src)
