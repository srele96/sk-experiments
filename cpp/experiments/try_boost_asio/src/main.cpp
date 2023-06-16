#include <iostream>

// Fix include errors in Visual Studio Code:
// https://stackoverflow.com/questions/45583473/include-errors-detected-in-vscode
#include "boost/asio.hpp"

int main() {
  boost::asio::io_context io;
  boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
  t.wait();
  std::cout << "Hello, world!" << std::endl;

  return 0;
}
