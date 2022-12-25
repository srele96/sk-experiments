#include <array>
#include <iostream>

int main() {
  const std::size_t side_length = 5;
  std::array<std::array<int, side_length>, side_length> graph{{
      {0, 1, 1, 1, 1},
      {1, 0, 1, 1, 1},
      {1, 1, 0, 1, 1},
      {1, 1, 1, 0, 1},
      {1, 1, 1, 1, 0},
  }};

  for (const auto &row : graph) {
    for (const auto &column : row) {
      std::cout << column << ' ';
    }
    std::cout << '\n';
  }

  return 0;
}
