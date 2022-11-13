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

  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_port = htons(3000);
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  std::cout << "Created address for server socket.\n";

  // https://stackoverflow.com/questions/21099041/why-do-we-cast-sockaddr-in-to-sockaddr-when-calling-bind
  bind(server, reinterpret_cast<SOCKADDR*>(&address), sizeof(address));
  std::cout << "Bound server socket to address.\n";

  listen(server, SOMAXCONN);
  std::cout << "Listening for incomming connections on the server socket.\n";

  std::cout << "Listening on: http://127.0.0.1:3000\n";
  // https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-accept
  // Pass null to ignore the information about the client.
  SOCKET client = accept(server, NULL, NULL);

  // https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-recv
  const int byte = 1024;
  char buffer[byte];
  // Save content of the request to the buffer.
  recv(client, buffer, byte, 0);
  std::cout << "Received:\n" << buffer << "\n";

  const char* send_people_json =
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: application/json\r\n"
      "Access-Control-Allow-Origin: *\r\n\r\n"
      "[{\"name\":\"John\"},{\"name\":\"Jane\"}]";
  send(client, send_people_json, strlen(send_people_json), 0);

  // Release the resources.
  closesocket(client);
  closesocket(server);
  WSACleanup();
  std::cout << "Released server socket resources.\n";
  return 0;
}
