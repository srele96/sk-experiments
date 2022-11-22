/*

/*

target_location = 'found' | 'to_begin' | 'to_end'
target_not_found = -1

binary_search(begin, end, predicate):
  if begin <= end
    half = floor(( begin + end ) / 2)

    result = predicate(half)

    switch (result):
      case target_location.found
        return half
      case target_location.to_begin
        return binary_search(begin, half - 1, predicate)
      case target_location.to_end
        return binary_search(half + 1, end, predicate)
      default
        Error. Unexpected target location.
  else
    return target_not_found

find_row(row_half):
  // Check if the target is in current row.
  if target >= matrix[row_half][col_begin] and
     target <= matrix[row_half][col_end]
    return target_location.found
  if target <= matrix[row_half][col_begin]
    return target_location.to_begin return
  target_location.to_end

find_col(col_half):
  if target === matrix[row][col_half]
    return target_location.found
  if target <= matrix[row][col_half]
    return target_location.to_begin
  return target_location.to_end

*/

* /
#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>

    namespace search_matrix {

  enum class value { found, to_begin, to_end };

  bool binary_search(int begin, int end,
                     const std::function<value(int)>& predicate) {
    if (begin < end) {
      const int half = std::floor((begin + end) / 2);
      const value result = predicate(half);

      switch (result) {
        case value::found: {
          // Value found.
          return true;
        }
        case value::to_begin: {
          // We checked the current one, so go towards the begin.
          return binary_search(begin, half - 1, predicate);
        }
        case value::to_end: {
          // We checked the current one, so go towards the end.
          return binary_search(half + 1, end, predicate);
        }
        default: {
          throw(std::logic_error("Predicate returned unexpected value!"));
        }
      }
    } else {
      // Value not found.
      return false;
    }
  }

}  // namespace search_matrix

int main() {
  const std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const int find_number = 11;

  std::function<search_matrix::value(int)> find_row = [&](int index) {
    if (find_number == numbers.at(index)) {
      return search_matrix::value::found;
    }
    if (find_number > numbers.at(index)) {
      return search_matrix::value::to_begin;
    }
    if (find_number < numbers.at(index)) {
      return search_matrix::value::to_end;
    }
    throw(std::logic_error("Unexpected error. All predicate checks failed!"));
  };

  const int begin_index = 0;
  const int end_index = 9;
  std::cout << search_matrix::binary_search(begin_index, end_index, find_row)
            << '\n';

  return 0;
}
