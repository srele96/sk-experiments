#ifndef DISPLAY_VECTORS_SCREEN_HPP
#define DISPLAY_VECTORS_SCREEN_HPP

#include <vector>

namespace display_vectors {

using display_value = char;
using display = std::vector<std::vector<display_value>>;

class screen {
 private:
  display _1d;
  display _2d;
  display _3d;

 public:
  screen();

  display get_1d() const;
  display get_2d() const;
  display get_3d() const;
};

}  // namespace display_vectors

#endif  // DISPLAY_VECTORS_SCREEN_HPP
