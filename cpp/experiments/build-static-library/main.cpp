#include <iostream>

#include "Point.hpp"

int main() {
  Point dot;
  std::cout << "Building a static library!";
  std::cout << '{' << dot.x_coordinate << ", " << dot.y_coordinate << '}';

  return 0;
}
