#include "../coordinate.hpp"

#include <functional>
#include <vector>

display_vectors::coordinate::coordinate(const std::vector<int>& vector)
    : position{display_vectors::point{4, 4}},
      move_along_axis{
          // horisontal
          [this](const int& move_by) {
            // reduce by negative value to move left
            // add positive value to move right
            position.x += move_by;
          },
          // vertical
          [this](const int& move_by) {
            // reduce by negative value to move down
            // reduce by positive value to move up
            position.y -= move_by;
          },
          // diagonal
          [this](const int& move_by) {
            // reduce by negative value to move right
            // reduce by positive value to move left
            position.x -= move_by;
            // add negative value to move up
            // add positive value to move down
            position.y += move_by;
          },
      } {
  set_position(vector);
}

void display_vectors::coordinate::set_position(const std::vector<int>& vector) {
  for (std::vector<int>::size_type i = 0; i != vector.size(); ++i) {
    int component = vector.at(i);
    std::function<void(const int&)> move_point_by = move_along_axis.at(i);
    move_point_by(component);
  }
}

display_vectors::point display_vectors::coordinate::get_position() const {
  return position;
}
