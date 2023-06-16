#include <iostream>

struct X {
  int value;

  bool operator<(const X& other) { return value < other.value; }
};

int main() {
  const X zero{0};
  const X one{1};
  const bool is_smaller = zero < one;  // Error

  return 0;
}
