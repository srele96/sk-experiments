add_executable(
  display_vectors

  main.cpp

  # ---------------------------------------------------------------------------
  # namespace
  display_vectors.hpp

  # header
  display_vectors/coordinate.hpp
  display_vectors/emulate_gui.hpp
  display_vectors/origin.hpp
  display_vectors/pixel.hpp
  display_vectors/screen.hpp

  # implementation
  display_vectors/impl/coordinate.cpp
  display_vectors/impl/emulate_gui.cpp
  display_vectors/impl/origin.cpp
  display_vectors/impl/pixel.cpp
  display_vectors/impl/screen.cpp

  # ---------------------------------------------------------------------------
  # namespace
  driver.hpp

  # header
  driver/run_emulator_gui.hpp

  # implementation
  driver/impl/run_emulator_gui.cpp
)

target_compile_options(
  display_vectors
  # I don't have the use case for this property, but I have to specify it.
  # Additionally, I don't know how does it affect my project.
  PRIVATE
  "-Wall;-Wextra;-Werror;-Wshadow;-Weffc++;-Wnon-virtual-dtor;-pedantic"
)
