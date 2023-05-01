set_current_dirname(PROJECT_NAME)

project(
  ${PROJECT_NAME}
  LANGUAGES CXX
  VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER clang++)

add_subdirectory(src)
