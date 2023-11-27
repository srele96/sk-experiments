// Use tutorial example to verify boost asio works.
// https://www.boost.org/doc/libs/1_82_0/doc/html/boost_asio/tutorial/tutdaytime3.html
#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

auto make_response() -> std::string {
  std::string response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Length: 13\r\n";
  response += "Connection: close\r\n";
  response += "\r\n";
  response += "Hello, World!";
  return response;
}

void handle_client(tcp::socket socket) {
  boost::asio::streambuf request;
  boost::asio::read_until(socket, request, "\r\n\r\n");

  std::string response = make_response();
  boost::asio::write(socket, boost::asio::buffer(response));
  socket.close();
}

auto main() -> int {
  try {
    boost::asio::io_context io_context;
    const boost::asio::ip::port_type port{8080};
    tcp::acceptor acceptor{io_context, tcp::endpoint{tcp::v4(), port}};
    std::cout << "Server listening on port 8080...\n";

    while (true) {
      tcp::socket socket{io_context};
      acceptor.accept(socket);
      handle_client(std::move(socket));
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << "\n";
  }

  return 0;
}
