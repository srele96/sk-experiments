#include <iostream>

struct X {
  int value;

  // See const before body
  bool operator<(const X& other) const { return value < other.value; }
};

int main() {
  X zero{0};
  X one{1};
  const bool is_smaller = zero < one;  // Ok

  return 0;
}
