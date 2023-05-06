// Use tutorial example to verify boost asio works.
// https://www.boost.org/doc/libs/1_82_0/doc/html/boost_asio/tutorial/tutdaytime3.html
#include "boost/asio.hpp"
#include "boost/asio/detail/chrono.hpp"
#include "boost/asio/steady_timer.hpp"
#include "iostream"

int main() {
  try {
    boost::asio::io_context io_context;

    boost::asio::steady_timer timer{io_context,
                                    boost::asio::chrono::seconds{1}};

    const std::string timer_string{" -> `timer.async_wait`\n"};
    std::cout << "Before" << timer_string;
    timer.async_wait([](const boost::system::error_code &error_code) {
      if (error_code) {
        std::cerr << error_code.message() << "\n";
      } else {
        std::cout << "Timer completed.\n";
      }
    });
    std::cout << "After" << timer_string;

    std::cout << "Waiting for timer to complete...\n";
    io_context.run();
  } catch (std::exception &error) {
    std::cerr << error.what() << "\n";
  }

  return 0;
}
