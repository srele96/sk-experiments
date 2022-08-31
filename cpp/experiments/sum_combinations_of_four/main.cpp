#include <iostream>
#include <vector>

std::vector<std::vector<int>> get_combinations_of_four_that_match_sum(
    std::vector<int> sample, int sum) {
  std::vector<std::vector<int>> combinations;

  int i, j, z, k, len = sample.size();

  for (i = 0; i < len - 3; i++) {
    for (j = i + 1; j < len - 2; j++) {
      for (z = j + 1; z < len - 1; z++) {
        for (k = z + 1; k < len; k++) {
          // found combination that matches sum
          if (sample.at(i) + sample.at(j) + sample.at(z) + sample.at(k) ==
              sum) {
            // the following operations take O(1) time
            std::vector<int> create_combination = {sample.at(i), sample.at(j),
                                                   sample.at(z), sample.at(k)};
            combinations.push_back(create_combination);
          }
        }
      }
    }
  }

  return combinations;
}

void print_combinations(std::vector<std::vector<int>> combinations) {
  if (combinations.size() == 0) {
    std::cout << "Combinations are empty, nothing to print!" << std::endl;
  } else {
    for (std::vector<int> c : combinations) {
      // we can be sure that each combination has four elements, so we can
      // access them like this
      std::cout << "[" << c.at(0) << ", " << c.at(1) << ", " << c.at(2) << ", "
                << c.at(3) << "]" << std::endl;
    }
  }
}

int main() {
  print_combinations(
      get_combinations_of_four_that_match_sum({2, 1, 10, 2, 3, 5, 6}, 8));

  return 0;
}
