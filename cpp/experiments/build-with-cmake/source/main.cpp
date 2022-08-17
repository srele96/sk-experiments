#include <iostream>

#include "Point.hpp"

int main() {
  Point p(7.5, 8.0);
  std::cout << "{" << p.x << ", " << p.y << "}";

  return 0;
}
