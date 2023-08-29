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

# Copy image directory because binary has to load assets relative to itself
# because I didn't find a better way to load static assets that the application
# requires.
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  # Make sure the directory exists
  COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/image
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/image $<TARGET_FILE_DIR:${PROJECT_NAME}>/image
)
