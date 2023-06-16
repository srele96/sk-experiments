#include "../pixel.hpp"

#include <vector>

display_vectors::pixel::pixel(
    display_vectors::display_value initial_display_value,
    const std::vector<int>& vector)
    : display_value{initial_display_value}, coordinate{vector} {}

display_vectors::coordinate display_vectors::pixel::get_coordinate() const {
  return coordinate;
}

display_vectors::display_value display_vectors::pixel::get_display_value()
    const {
  return display_value;
};
