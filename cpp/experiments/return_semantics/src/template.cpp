#include <iostream>
#include <string>

template <typename T>
void run_without_param(const T& function) {
  function();
}

template <typename T>
void run_with_param(const T& function) {
  function("Heya!");
}

int main() {
  run_without_param([]() { std::cout << "Run Without Param\n"; });
  run_with_param([](std::string param) {
    std::cout << "Run With Param -> " << param << "\n";
  });
  run_with_param([](const std::string& param) {
    std::cout << "Run With Param -> " << param << "\n";
  });

  return 0;
}
