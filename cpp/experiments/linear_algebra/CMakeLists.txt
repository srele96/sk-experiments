cmake_minimum_required(VERSION 3.14)

project(
  linear_algebra
  LANGUAGES CXX
  VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 23)

# Place executable in the build/<executable_name>
# I just want to easily run the executable without going to build/src
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(./src)
