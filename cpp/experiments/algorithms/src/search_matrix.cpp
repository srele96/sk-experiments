/*



find(grid, row_begin, row_end, column_begin, column_end, value):
  if begin of rows is smaller than the end of rows
    take value between begin and end of rows

    if value is at the begin of this row or value is at the end of this row
      found it
    else if value is above this row
      search up
    else if value is below this row
      search below
    else
      if begin of columns is smaller than the end of columns
        take value between begin and end of columns

        if the value between begin and end is same as searched value
          found it
        else if value is higher
          search right
        else search left
      else
        value not found
  else
    value not found



binary_search(begin, end, predicate):
  if begin smaller than end
    calculate half between begin and end

    result = predicate(pass the half)

    if result is found
    elif result is less
    elif result is greater
    else i didn't expect to get here, incorrect return value
  else
    value not found



row = binary_search(row_begin, row_end, find_row)
if row
  col = binary_search(col_begin, col_end, find_col)
  if col
    value found
  else
    value not found
else:
  value not found





binary_search(begin, end, predicate)
  if begin < end
    half = floor ( ( begin + end ) / 2 )
    result = predicate(half)

    if result == 0 // result is found
      return true // return something to indicate that the result is found
    elif result == 1 // result is value smaller than the value on half
      binary_search(begin, half - 1, predicate) // search from begin to half
    elif result is value larger than the value on half
      binary_search(half + 1, end, predicate) // search from half to end
    else
      error, predicate returned unexpected value
  else
    return false // return something to indicate that the result is not found

find_value(half)
  if value == numbers[half]
    return value found
  elif value < numbers[half]
    return search from begin to half
  else
    return search from half to end

value = binary_search(begin, end, find_half)
if value
  value found
else
  value not found

*/
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
        // We checked the current one, go towards the end.
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
