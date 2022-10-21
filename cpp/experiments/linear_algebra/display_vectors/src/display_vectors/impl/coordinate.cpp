#include "../coordinate.hpp"

#include <functional>
#include <vector>

display_vectors::coordinate::coordinate(const std::vector<int>& vector)
    : position{display_vectors::point{4, 4}},
      move_along_axis{
          {
              [this](const int& move_by) { position.x += move_by; },
              [this](const int& move_by) { position.y -= move_by; },
              [this](const int& move_by) {
                position.x -= move_by;
                position.y += move_by;
              },
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
