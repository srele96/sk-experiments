#include <iostream>
#include <string>
#include <vector>

namespace practice_recursion {

std::vector<int> pascals_row(const int n) {
  std::vector<int> result;
  if (n == 1) {
    result.push_back(1);
  } else {
    auto previous_row{pascals_row(n - 1)};
    // Left edge is always 1.
    result.push_back(1);
    // Start from one to prevent underflow.
    for (std::size_t i{1}; i != previous_row.size(); ++i) {
      // Add previous and current value.
      result.push_back(previous_row.at(i - 1) + previous_row.at(i));
    }
    // Right edge is always 1.
    result.push_back(1);
  }
  return result;
}

}  // namespace practice_recursion

namespace test {

void stream_row(const std::vector<int>& row, std::ostream& os) {
  for (auto it{row.begin()}; it != row.end(); ++it) {
    os << *it << " ";
  }
}

}  // namespace test

int main() {
  const int row_begin{1};
  const int row_end{5};
  const std::string newline{"\n"};

  // Print rows.
  for (int row{row_begin}; row <= row_end; ++row) {
    test::stream_row(practice_recursion::pascals_row(row), std::cout);
    std::cout << newline;
  }

  return 0;
}
