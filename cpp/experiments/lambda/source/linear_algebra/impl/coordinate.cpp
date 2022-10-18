#include "../coordinate.hpp"

#include <iostream>
#include <string>
#include <vector>

linear_algebra::coordinate::coordinate(
    linear_algebra::position initial_position)
    : position{initial_position},
      // movements represent axes in coordinate system
      movements{
          // horisontal
          [this](const int& move_by) {
            // reduce by negative value to move left
            // add positive value to move right
            position.column += move_by;
          },
          // vertical
          [this](const int& move_by) {
            // reduce by negative value to move down
            // reduce by positive value to move up
            position.row -= move_by;
          },
          // diagonal
          [this](const int& move_by) {
            // reduce by negative value to move right
            // reduce by positive value to move left
            position.column -= move_by;
            // add negative value to move up
            // add positive value to move down
            position.row += move_by;
          },
      } {}

void linear_algebra::coordinate::print_formatted_state(
    const std::string& message) const {
  std::cout << message << " (" << position.row << ", " << position.column
            << ")\n";
}

void linear_algebra::coordinate::move_and_print_each(
    const std::vector<int>& vector) {
  // for simplicity just assume vector is always the same length as movements
  // problem: i should prefer iterators wherever possible
  // https://stackoverflow.com/questions/12702561/iterate-through-a-c-vector-using-a-for-loop
  // move coordinate for each matching component
  for (std::vector<int>::size_type i = 0; i != vector.size(); ++i) {
    movements.at(i)(vector.at(i));
    print_formatted_state("Move to:");
  }
}
