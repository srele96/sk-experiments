#include <iostream>
#include <vector>

namespace algorithm {
namespace result {

constexpr std::size_t not_found = -1;

}
}  // namespace algorithm

namespace algorithm {

std::size_t binary_search(const std::vector<int>& numbers, int number) {
  std::size_t begin = 0;
  std::size_t end = numbers.size() - 1;

  while (begin <= end) {
    const std::size_t half = (begin + end) / 2;
    const int current_number = numbers.at(half);

    if (current_number == number) {
      return half;
    }

    if (current_number > number) {
      end = half - 1;
    } else {
      begin = half + 1;
    }
  }

  return result::not_found;
}

}  // namespace algorithm

namespace util {

void print_result(bool found, int number) {
  if (found) {
    std::cout << "Number found = " << number << '\n';
  } else {
    std::cout << "Number not found = " << number << '\n';
  }
}

void search_and_print_result(const std::vector<int>& numbers, int number) {
  const std::size_t index = algorithm::binary_search(numbers, number);
  const bool found = index != algorithm::result::not_found;

  util::print_result(found, number);
}

}  // namespace util

int main() {
  const int number = 5;
  const std::vector<int> numbers{1, 2, 3, 4, number, 6, 7, 8, 9, 10};

  util::search_and_print_result(numbers, number);

  const int wont_be_found = 15;

  util::search_and_print_result(numbers, wont_be_found);

  return 0;
}
