#include "../screen.hpp"

#include <vector>

display_vectors::screen::screen()
    : _1d{ // sync with origin.hpp which has to contain center
        {
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
      },
      _2d{ // sync with origin.hpp which has to contain center
          {
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
      },
      _3d{ // sync with origin.hpp which has to contain center
          {
              {' ', ' ', ' ', ' ', 'y', ' ', ' ', ' ', 'z'},
              {' ', ' ', ' ', ' ', 'y', ' ', ' ', 'z', ' '},
              {' ', ' ', ' ', ' ', 'y', ' ', 'z', ' ', ' '},
              {' ', ' ', ' ', ' ', 'y', 'z', ' ', ' ', ' '},
              {'x', 'x', 'x', 'x', '0', 'x', 'x', 'x', 'x'},
              {' ', ' ', ' ', 'z', 'y', ' ', ' ', ' ', ' '},
              {' ', ' ', 'z', ' ', 'y', ' ', ' ', ' ', ' '},
              {' ', 'z', ' ', ' ', 'y', ' ', ' ', ' ', ' '},
              {'z', ' ', ' ', ' ', 'y', ' ', ' ', ' ', ' '},
          },
      } {}

display_vectors::display display_vectors::screen::get_1d() const { return _1d; }

display_vectors::display display_vectors::screen::get_2d() const { return _2d; }

display_vectors::display display_vectors::screen::get_3d() const { return _3d; }
