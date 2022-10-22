add_executable(
  display_vectors

  main.cpp

  # ---------------------------------------------------------------------------

  display_vectors.hpp

  display_vectors/axis.hpp
  display_vectors/coordinate.hpp
  display_vectors/emulate_gui.hpp
  display_vectors/pixel.hpp
  display_vectors/screen.hpp

  display_vectors/impl/coordinate.cpp
  display_vectors/impl/emulate_gui.cpp
  display_vectors/impl/pixel.cpp
  display_vectors/impl/screen.cpp

  # ---------------------------------------------------------------------------

  driver.hpp

  driver/run_terminal_gui_emulator.hpp

  driver/impl/run_terminal_gui_emulator.cpp
)

target_compile_options(
  display_vectors
  PRIVATE
  "-Wall;-Wextra;-Werror;-Wshadow;-Weffc++;-Wnon-virtual-dtor;-pedantic"
)
