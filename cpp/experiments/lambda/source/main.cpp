#include <vector>

#include "linear_algebra.hpp"

int main() {
  const linear_algebra::position CENTER{3, 3};
  linear_algebra::coordinate coordinate{CENTER};

  coordinate.print_formatted_state("Before movement:");

  std::vector<int> destination{2, 2, -1};

  coordinate.move_and_print_each(destination);
  coordinate.print_formatted_state("After movement:");

  return 0;
}
