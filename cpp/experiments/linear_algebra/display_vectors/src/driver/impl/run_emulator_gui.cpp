#include "../run_emulator_gui.hpp"

#include <iostream>
#include <string>

#include "../../display_vectors.hpp"

void driver::run_terminal_gui_emulator() {
  display_vectors::screen screen;

  const display_vectors::axis::_1d v_1d{1};
  const display_vectors::axis::_1d w_1d{-2};

  display_vectors::emulate_gui terminal_1d{
      screen.get_1d(),
      {
          display_vectors::pixel{
              'v',
              {
                  v_1d.x,
              },
          },
          display_vectors::pixel{
              'w',
              {
                  w_1d.x,
              },
          },
      },
  };

  std::string split_and_emphasize_displays = "\n---------\n";
  std::cout << split_and_emphasize_displays;

  terminal_1d.render();
  std::cout << split_and_emphasize_displays;

  const display_vectors::axis::_2d v_2d{1, -2};
  const display_vectors::axis::_2d w_2d{-2, 2};

  display_vectors::emulate_gui terminal_2d{
      screen.get_2d(),
      {
          display_vectors::pixel{
              'v',
              {
                  v_2d.x,
                  v_2d.y,
              },
          },
          display_vectors::pixel{
              'w',
              {
                  w_2d.x,
                  w_2d.y,
              },
          },
      },
  };

  terminal_2d.render();
  std::cout << split_and_emphasize_displays;

  const display_vectors::axis::_3d v_3d{1, -2, 2};
  const display_vectors::axis::_3d w_3d{-2, 2, -1};

  display_vectors::emulate_gui terminal_3d{
      screen.get_3d(),
      {
          display_vectors::pixel{
              'v',
              {
                  v_3d.x,
                  v_3d.y,
                  v_3d.z,
              },
          },
          display_vectors::pixel{
              'w',
              {
                  w_3d.x,
                  w_3d.y,
                  w_3d.z,
              },
          },
      },
  };

  terminal_3d.render();
  std::cout << split_and_emphasize_displays;
}
