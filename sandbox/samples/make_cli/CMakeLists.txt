set_current_dirname(CURRENT_DIRECTORY_NAME)

project(
  ${CURRENT_DIRECTORY_NAME}
  LANGUAGES CXX
  VERSION 0.0.1
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER clang++)

add_executable(
  ${PROJECT_NAME}

  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${Boost_INCLUDE_DIRS}
)
