add_executable(
  tcp_socket_server

  main.cpp
)

# Calls to WSAStartup fail without this.
# Error: undefined reference to `__imp_WSAStartup'
target_link_libraries(tcp_socket_server ws2_32.lib)
