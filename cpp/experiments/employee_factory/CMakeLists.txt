cmake_minimum_required(VERSION 3.14)

project(
  employee_factory
  LANGUAGES CXX
  VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 17)

# https://stackoverflow.com/questions/9345792/cmake-executable-location
# set desired output location of our executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_compile_options(-Wall -Wextra -Werror -Wshadow -Weffc++ -Wnon-virtual-dtor -pedantic)
add_subdirectory(./source)
