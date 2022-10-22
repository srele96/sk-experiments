#include "../screen.hpp"

#include <vector>

display_vectors::screen::screen()
    // sync with origin.hpp which has to contain center
    : _1d{
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {'x', 'x', 'x', 'x', '0', 'x', 'x', 'x', 'x'},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      },
      // sync with origin.hpp which has to contain center
      _2d{
          {' ', ' ', ' ', ' ', 'y', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', 'y', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', 'y', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', 'y', ' ', ' ', ' ', ' '},
          {'x', 'x', 'x', 'x', '0', 'x', 'x', 'x', 'x'},
          {' ', ' ', ' ', ' ', 'y', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', 'y', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', 'y', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', 'y', ' ', ' ', ' ', ' '},
      },
      // sync with origin.hpp which has to contain center
      _3d{
          {' ', ' ', ' ', ' ', 'y', ' ', ' ', ' ', 'z'},
          {' ', ' ', ' ', ' ', 'y', ' ', ' ', 'z', ' '},
          {' ', ' ', ' ', ' ', 'y', ' ', 'z', ' ', ' '},
          {' ', ' ', ' ', ' ', 'y', 'z', ' ', ' ', ' '},
          {'x', 'x', 'x', 'x', '0', 'x', 'x', 'x', 'x'},
          {' ', ' ', ' ', 'z', 'y', ' ', ' ', ' ', ' '},
          {' ', ' ', 'z', ' ', 'y', ' ', ' ', ' ', ' '},
          {' ', 'z', ' ', ' ', 'y', ' ', ' ', ' ', ' '},
          {'z', ' ', ' ', ' ', 'y', ' ', ' ', ' ', ' '},
      } {}

display_vectors::display display_vectors::screen::get_1d() const { return _1d; }

display_vectors::display display_vectors::screen::get_2d() const { return _2d; }

display_vectors::display display_vectors::screen::get_3d() const { return _3d; }
