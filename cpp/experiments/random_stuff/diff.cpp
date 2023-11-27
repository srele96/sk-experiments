#include <iostream>

int main() {
  const int initial_a{50};
  int a{initial_a};

  const int* p_a{&a};
  std::cout << "p_a = " << a << ", " << *p_a << "\n";

  const int* const p_b{&a};
  std::cout << "p_b = " << a << ", " << *p_b << "\n";

  const int initial_b{100};
  int b{initial_b};

  const int* p_c{&b};
  std::cout << "p_c = " << b << ", " << *p_c << "\n";

  const int* const p_d{&b};
  std::cout << "p_d = " << b << ", " << *p_d << "\n";

  // I figured, the pointer is constant.
  // p_a = nullptr;
  // p_b = nullptr;

  return 0;
}
