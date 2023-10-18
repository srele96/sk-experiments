# Central configuration file.
# This file acts as controller for the content of the sandbox. All shared
# configuration, variables, and everything that any module or sample may depend
# on should be here. Be careful when declaring shared setup because any kind of
# global setup is evil.

cmake_minimum_required(VERSION 3.20)
project(sandbox)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Find Boost package installed by vcpkg.

# The find_package(Boost REQUIRED) command in CMake is used to locate the Boost
# installation in your system and set up the necessary variables for your project
# to use Boost. However, when you use it without the COMPONENTS keyword, it's
# primarily geared towards finding the header files for header-only libraries in
# Boost, since Boost has many libraries that are implemented entirely as header
# files without separate compiled binaries.

# If you need to link against compiled Boost libraries (like program_options),
# you need to specify them using the COMPONENTS keyword. This tells CMake
# explicitly that you're looking for specific compiled libraries within the Boost
# library collection, and it will set up the necessary variables for linking.
find_package(Boost REQUIRED COMPONENTS program_options)

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
