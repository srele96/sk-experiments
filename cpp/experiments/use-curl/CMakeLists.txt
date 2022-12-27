cmake_minimum_required(VERSION 3.14)

project(use-curl)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wshadow -Weffc++ -Wnon-virtual-dtor")

# https://cmake.org/cmake/help/latest/module/FetchContent.html
include(FetchContent)

FetchContent_Declare(
  curl
  GIT_REPOSITORY https://github.com/curl/curl.git
  GIT_TAG c12fb3ddaf48e709a7a4deaa55ec485e4df163ee # release 7.87.0
)

FetchContent_MakeAvailable(curl)

add_subdirectory(src)
