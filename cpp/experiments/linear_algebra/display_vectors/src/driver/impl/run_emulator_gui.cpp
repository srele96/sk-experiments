#include "../run_emulator_gui.hpp"

#include <iostream>
#include <string>

#include "../../display_vectors.hpp"

void driver::run_terminal_gui_emulator() {
  display_vectors::screen screen;

  display_vectors::emulate_gui terminal_1d{
      screen.get_1d(),
      {
          display_vectors::pixel{'v', {1}},
          display_vectors::pixel{'w', {-2}},
      },
  };

  std::string split_and_emphasize_displays = "\n---------\n";
  std::cout << split_and_emphasize_displays;
  terminal_1d.render();
  std::cout << split_and_emphasize_displays;

  display_vectors::emulate_gui terminal_2d{
      screen.get_2d(),
      {
          display_vectors::pixel{'v', {1, -2}},
          display_vectors::pixel{'w', {-2, 2}},
      },
  };

  terminal_2d.render();
  std::cout << split_and_emphasize_displays;

  display_vectors::emulate_gui terminal_3d{
      screen.get_3d(),
      {
          display_vectors::pixel{'v', {1, -2, 2}},
          display_vectors::pixel{'w', {-2, 2, -1}},
      },
  };

  terminal_3d.render();
  std::cout << split_and_emphasize_displays;
}
