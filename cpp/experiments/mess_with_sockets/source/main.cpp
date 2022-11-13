#include <winsock2.h>

#include <iostream>

// The application has to call the WSAStartup(); before using sockets.
// We have to release the resources at the end by calling WSACleanup();
//
// The pattern of using sockets in C++ is:
//
//  1. Create type of connection. TCP IPv4
//  2. Create socket using the type of connection.
//  3. Bind socket.
//  4. Listen to the socket.
//  5. Accept connections from the socket.
//  6. Write a response to the accepted socket.
//  7. Close the socket after usage to release the resources.
int main() {
  WSADATA wsaData;
  const int two = 2;
  const int version_2_2 = MAKEWORD(two, two);
  // https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsastartup#remarks
  WSAStartup(version_2_2, &wsaData);

  // https://en.wikipedia.org/wiki/Network_socket#Types
  SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  // Release the resources.
  WSACleanup();
  return 0;
}
