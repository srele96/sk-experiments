add_executable(
  employee_factory

  main.cpp

  role/interface.h
  role/interface/employee.h

  role.h
  role/janitor.h
  role/janitor.cpp
  role/tester.h
  role/tester.cpp
  role/maintenance.h
  role/maintenance.cpp
  role/operator.h
  role/operator.cpp
)

#[[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
I am unsure if I should use private, public, or interface scope.
I've read two articles about those properties:
  - https://cmake.org/cmake/help/latest/command/target_compile_options.html
  - https://leimao.github.io/blog/CMake-Public-Private-Interface/

However, I still can't comprehend which one to use.

Use the most restrictive one and hope that the build breaks early to be able
to fix it. I guess the most restrice one is PRIVATE.

Resource where I found how to use target_compile_options:
- https://gist.github.com/sonictk/8ce00c6019d3a19056c054e485326434
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]]

target_compile_options(
  employee_factory
  PRIVATE
  "-Wall;-Wextra;-Werror;-Wshadow;-Weffc++;-Wnon-virtual-dtor;-pedantic"
)
