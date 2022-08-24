#include <iostream>

std::string get_text() {
  return "get text bla bla bla";
}

int main() {
  std::cout << "Hello world" << std::endl;
  std::cout << get_text() << std::endl;
}
