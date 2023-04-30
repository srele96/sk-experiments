cmake_minimum_required(VERSION 3.14)

project(
  print_something
  LANGUAGES CXX
  VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER clang++)

add_subdirectory(src)
