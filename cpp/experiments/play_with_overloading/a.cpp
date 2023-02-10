#include <iostream>

struct X {
  int value;

  bool operator<(const X& other) { return value < other.value; }
};

int main() {
  X zero{0};
  X one{1};
  const bool is_smaller = zero < one;  // Ok

  return 0;
}
