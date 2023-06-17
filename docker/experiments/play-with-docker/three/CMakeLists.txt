cmake_minimum_required(VERSION 3.20)
project(three)

# https://stackoverflow.com/questions/45933732/how-to-specify-a-compiler-in-cmake
# The answer says this is bad practice but it's ok because I probably won't
# continue work on this sample.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER clang++)

# Expect to provide the two on linux by using `apt-get` described in `README.md`
find_library(PQ_LIB pq)
find_library(PQXX_LIB pqxx)

add_executable(three main.cpp)

target_link_libraries(three ${PQ_LIB} ${PQXX_LIB})
