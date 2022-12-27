add_executable(
  use-curl

  main.cpp
)

target_link_libraries(use-curl PRIVATE curl)
