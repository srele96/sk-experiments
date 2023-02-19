add_executable(
  ${PROJECT_NAME}

  ${PROJECT_SOURCE_DIR}/src/main.cpp
)

# After using example boost:asio one of the errors that I've got was:
# undefined reference to `__imp_WSAStartup'
# From my previous example for socket programming using C++ I assumed that I
# had to link with ws2_32.lib
target_link_libraries(${PROJECT_NAME} ws2_32.lib)
