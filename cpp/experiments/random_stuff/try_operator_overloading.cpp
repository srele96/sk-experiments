#include <iostream>
#include <string>

namespace try_operator_overloading {

struct node {
  int value;

  bool operator<(const node& other) const { return value < other.value; }
  bool operator>(const node& other) const { return value > other.value; }
};

}  // namespace try_operator_overloading

int main() {
  constexpr int left_value{5};
  try_operator_overloading::node left{left_value};

  constexpr int right_value{10};
  try_operator_overloading::node right{right_value};

  const std::string endline{".\n"};

  std::cout << "Using less than left is "
            << (left < right ? "smaller" : "greater") << endline;
  std::cout << "Using greater than left is "
            << (left > right ? "greater" : "smaller") << endline;

  return 0;
}
