add_executable(
  mess_with_sockets

  main.cpp
)

# Calls to WSAStartup fail without this.
# Error: undefined reference to `__imp_WSAStartup'
target_link_libraries(mess_with_sockets ws2_32.lib)
