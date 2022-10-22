#ifndef DISPLAY_VECTORS_DISPLAY_VECTORS_EMULATE_GUI_HPP
#define DISPLAY_VECTORS_DISPLAY_VECTORS_EMULATE_GUI_HPP

#include "pixel.hpp"
#include "screen.hpp"

namespace display_vectors {

class emulate_gui {
 private:
  // I am unfortunate that I have to write code unambiguous like this. It is not
  // clear why the screen is of display type. I will tell you why. I designed
  // the algorithm with a global variable in mind. C++ does not like that, but I
  // do not want to rework the whole logic. I have spent the last four weeks
  // designing an algorithm to draw vectors in the terminal. I used two entire
  // notebooks in the first two weeks to figure it out. Then, I spent next week
  // designing it and last week procrastinating. I will implement it as is and
  // live with that mistake. My goal is to continue learning linear algebra.
  display_vectors::display screen;

  // Get every vector's x and y position and replace the default pixel with its
  // value.
  void replace_default_pixels(
      const std::vector<display_vectors::pixel>& pixels);

 public:
  emulate_gui(display_vectors::display initial_screen,
              const std::vector<display_vectors::pixel>& pixels);

  void render() const;
};

};  // namespace display_vectors

#endif  // DISPLAY_VECTORS_DISPLAY_VECTORS_EMULATE_GUI_HPP
