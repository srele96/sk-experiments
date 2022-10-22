#ifndef DISPLAY_VECTORS_DISPLAY_VECTORS_COORDINATE_HPP
#define DISPLAY_VECTORS_DISPLAY_VECTORS_COORDINATE_HPP

#include <functional>
#include <vector>

namespace display_vectors {

struct point {
  int x;
  int y;
};

class coordinate {
 private:
  display_vectors::point position;
  std::vector<std::function<void(int)>> move_along_axis;
  void set_position(const std::vector<int>& vector);

 public:
  explicit coordinate(const std::vector<int>& vector);

  display_vectors::point get_position() const;
};

};  // namespace display_vectors

#endif  // DISPLAY_VECTORS_COORDINATE_HPP
