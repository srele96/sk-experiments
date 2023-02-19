cmake_minimum_required(VERSION 3.14)

project(
  try_boost_asio
  LANGUAGES CXX
  VERSION 0.1.0
)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
# Can't use -Werror, here is quote from the Boost documentation:
#
#   Don't be alarmed if you see compiler warnings originating in Boost
#   headers. We try to eliminate them, but doing so isn't always practical.
#   Errors are another matter. If you're seeing compilation errors at this
#   point in the tutorial, check to be sure you've copied the example program
#   correctly and that you've correctly identified the Boost root directory.
# https://www.boost.org/doc/libs/1_80_0/more/getting_started/windows.html#id34
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# I couldn't make CMake find boost version 1.81.0 even thought I positioned it
# in the correct directory `C:\Program FIles\boost\boost_1_81_0`. After
# printing out information that the FindBoost.cmake was searching for I saw
# that there are many versions, but not 1.81.0. I thought that FindBoost.cmake
# is not up to date so I downloaded version 1.80.0 and CMake was able to find
# Boost, I was right.
# set(Boost_DEBUG 1) # Save debug information for later usage
# https://stackoverflow.com/questions/3808775/cmake-doesnt-find-boost
#
# Don't use COMPONENTS, read the comment on StackOverflow below.
# https://stackoverflow.com/questions/71610458/could-not-find-boost-missing-system-found-suitable-versihow-on-1-78-0-min
find_package(Boost 1.79.0)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
else()
  message(FATAL_ERROR "Boost not found")
endif()

add_subdirectory(./src)
