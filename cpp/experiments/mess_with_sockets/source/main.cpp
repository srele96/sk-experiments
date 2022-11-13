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
  std::cout << "Initialized socket server.\n";

  // https://en.wikipedia.org/wiki/Network_socket#Types
  SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  std::cout << "Created server socket.\n";

  const int PORT = 3000;

  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_port = PORT;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  std::cout << "Created address for server socket.\n";

  // https://stackoverflow.com/questions/21099041/why-do-we-cast-sockaddr-in-to-sockaddr-when-calling-bind
  bind(server, reinterpret_cast<SOCKADDR*>(&address), sizeof(address));
  std::cout << "Bound server socket to address.\n";

  listen(server, SOMAXCONN);
  std::cout << "Listening for incomming connections on the server socket.\n";

  std::cout << "Accepting request on: http://127.0.0.1:" << PORT << "\n";
  // https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-accept
  // Pass null to ignore the information about the client.
  SOCKET client = accept(server, NULL, NULL);

  // Release the resources.
  closesocket(server);
  WSACleanup();
  std::cout << "Released server socket resources.\n";
  return 0;
}
