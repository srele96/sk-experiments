#include <iostream>
#include <unordered_set>

namespace cpp_constructs {

const int any_number = 10;
// Default parameter is a value known at compile time. The compiler doesn't need
// to figure out what the value is. It doesn't need to evaluate the value, for
// example an increment in the function declaration would need to be evaluated
// at compile time.
void print_default_parameter(int val = any_number) {
  std::cout << "Value = " << val;
}

}  // namespace cpp_constructs

namespace util {

void insert_and_print_result(std::unordered_set<int>& numbers, int number) {
  if (const auto& result = numbers.insert(number); result.second) {
    std::cout << "Insertion success.\n";
  } else {
    std::cout << "Insertion fail.\n";
  }
}

void print_numbers(const std::unordered_set<int>& numbers) {
  for (const auto number : numbers) {
    std::cout << number << '\n';
  }
}

}  // namespace util

int main() {
  std::unordered_set<int> numbers;

  cpp_constructs::print_default_parameter();
  std::cout << '\n';
  const int different_than_default = 5;
  cpp_constructs::print_default_parameter(different_than_default);
  std::cout << '\n';

  const int some_number{1};
  util::insert_and_print_result(numbers, some_number);
  util::insert_and_print_result(numbers, some_number);
  const int some_other{2};
  util::insert_and_print_result(numbers, some_other);

  util::print_numbers(numbers);

  return 0;
}
