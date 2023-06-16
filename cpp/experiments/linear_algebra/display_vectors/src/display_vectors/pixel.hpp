#ifndef DISPLAY_VECTORS_DISPLAY_VECTORS_PIXEL_HPP
#define DISPLAY_VECTORS_DISPLAY_VECTORS_PIXEL_HPP

#include <vector>

#include "coordinate.hpp"
#include "screen.hpp"

namespace display_vectors {

class pixel {
 private:
  display_vectors::display_value display_value;
  display_vectors::coordinate coordinate;

 public:
  pixel(display_vectors::display_value initial_display_value,
        const std::vector<int>& vector);

  display_vectors::coordinate get_coordinate() const;
  display_vectors::display_value get_display_value() const;
};

};  // namespace display_vectors

#endif  // DISPLAY_VECTORS_PIXEL_HPP
