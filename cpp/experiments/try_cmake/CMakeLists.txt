cmake_minimum_required(VERSION 3.20)

project(try-cmake VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/module")

include(GenerateVersionInfo)

message(STATUS "TRY_CMAKE_PROJECT_VERSION: ${TRY_CMAKE_PROJECT_VERSION}")
# Oopsie! I can access variables within the module.
message(STATUS "GIT_TAG: ${GIT_TAG}")
