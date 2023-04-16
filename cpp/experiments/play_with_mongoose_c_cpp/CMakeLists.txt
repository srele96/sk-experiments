# https://www.scivision.dev/cmake-changelog/
cmake_minimum_required(VERSION 3.20)

project(
  asd
  LANGUAGES CXX
  VERSION 0.1.0
)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./src)
