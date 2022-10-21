#include "../emulate_gui.hpp"

#include <iostream>
#include <utility>
#include <vector>

display_vectors::emulate_gui::emulate_gui(
    display_vectors::display initial_screen,
    const std::vector<display_vectors::pixel>& pixels)
    : screen{std::move(initial_screen)} {
  replace_default_pixels(pixels);
}

void display_vectors::emulate_gui::replace_default_pixels(
    const std::vector<display_vectors::pixel>& pixels) {
  for (const display_vectors::pixel& pixel : pixels) {
    display_vectors::point position = pixel.get_coordinate().get_position();
    screen.at(position.x).at(position.y) = pixel.get_display_value();
  }
}

void display_vectors::emulate_gui::render() const {
  for (const auto& row : screen) {
    for (const auto& pixel : row) {
      std::cout << pixel;
    }
    std::cout << '\n';
  }
}
