set_current_dirname(CURRENT_DIRECTORY_NAME)

project(
  ${CURRENT_DIRECTORY_NAME}
  LANGUAGES CXX
  VERSION 0.1.0
)

add_executable(
  ${PROJECT_NAME}
  main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE wx::core wx::base)
