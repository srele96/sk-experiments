# Central configuration file.
# This file acts as controller for the content of the sandbox. All shared
# configuration, variables, and everything that any module or sample may depend
# on should be here. Be careful when declaring shared setup because any kind of
# global setup is evil.

cmake_minimum_required(VERSION 3.14)
project(sandbox)

# setup libraries

add_subdirectory(modules)
add_subdirectory(samples)
