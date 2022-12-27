cmake_minimum_required(VERSION 3.14)

project(use-curl)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wshadow -Weffc++ -Wnon-virtual-dtor")

add_subdirectory(src)
