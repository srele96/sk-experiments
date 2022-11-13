#include <winsock2.h>

#include <iostream>

int main() {
  WSADATA wsaData;
  const int two = 2;
  const int version_2_2 = MAKEWORD(two, two);
  // https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsastartup#remarks
  WSAStartup(version_2_2, &wsaData);

  // Release the resources.
  WSACleanup();
  return 0;
}
