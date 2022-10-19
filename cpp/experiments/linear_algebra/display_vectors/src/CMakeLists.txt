add_executable(
  display_vectors

  main.cpp
)

target_compile_options(
  display_vectors
  # I don't have the use case for this property, but I have to specify it.
  # Additionally, I don't know how does it affect my project.
  PRIVATE
  "-Wall;-Wextra;-Werror;-Wshadow;-Weffc++;-Wnon-virtual-dtor;-pedantic"
)
