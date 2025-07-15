#include <bits/stdc++.h>

struct A {
  int maximum_sum_sub_array(const std::vector<int>& numbers, int size) {
    int max_sum{0};
    int current_sum{0};
    int start_index{0};

    for (int end_index{0}; end_index < numbers.size(); ++end_index) {
      current_sum += numbers[end_index];

      if (end_index >= size - 1) {
        max_sum = std::max(max_sum, current_sum);
        current_sum -= numbers[start_index];
        ++start_index;
      }
    }

    return max_sum;
  }

  void operator()() {
    std::vector<int> numbers{9, 2, 1, 5, 1, 3, 2};
    int size{3};
    int result{maximum_sum_sub_array(numbers, size)};

    std::cout << "Maximum sum of sub-array of size " << size << " is " << result
              << "\n";
  }
};

struct B {
  void operator()() {
    std::vector<std::vector<int>> grid{
        {1, 2, 3},  //
        {4, 1, 5},  //
        {6, 7, 1}   //
    };

    struct Solve {
      std::vector<std::vector<int>>& m_grid;

      Solve(std::vector<std::vector<int>>& grid) m_grid{grid} {};

      int operator()() {}
    };

    std::cout << Solve{grid}();
  }
};

int main() {
  A{}();
  B{}();

  return 0;
}
