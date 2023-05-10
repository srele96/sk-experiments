# Central configuration file.
# This file acts as controller for the content of the sandbox. All shared
# configuration, variables, and everything that any module or sample may depend
# on should be here. Be careful when declaring shared setup because any kind of
# global setup is evil.

cmake_minimum_required(VERSION 3.20)
project(sandbox)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Find Boost package installed by vcpkg.
find_package(Boost REQUIRED)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# The simplest way I could find to get the current directory name.
# Useful when setting sample or module name to the current directory name.
function(set_current_dirname var)
  cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME current_dirname)
  set(${var} ${current_dirname} PARENT_SCOPE)
endfunction()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

add_subdirectory(modules)
add_subdirectory(samples)
