cmake_minimum_required(VERSION 3.20)

project(
  cpp_python_binding
  LANGUAGES CXX
  VERSION 0.1.0
)

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)

# cmake was using the python from the virtual environment hence it depended on the python 3.11 and my machine had python 3.10
message(STATUS "Found Python: ${Python_EXECUTABLE} (version ${Python_VERSION})")

# pybind11 method:
# pybind11_add_module(MyModule1 src1.cpp)

# Python method:
Python_add_library(example example.cpp)
target_link_libraries(example PRIVATE pybind11::headers)
set_target_properties(example PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION ON
    CXX_VISIBILITY_PRESET "default"
    VISIBILITY_INLINES_HIDDEN ON
)
