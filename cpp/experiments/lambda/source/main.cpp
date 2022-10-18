#include <vector>

#include "linear_algebra.hpp"

int main() {
  const linear_algebra::position CENTER{3, 3};
  linear_algebra::coordinate coordinate_v{CENTER};

  coordinate_v.print_formatted_state("Before movement:");

  std::vector<int> vector_v{2, 2, -1};

  coordinate_v.move_and_print_each(vector_v);
  coordinate_v.print_formatted_state("After movement:");

  return 0;
}
