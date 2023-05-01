# Central configuration file.
# This file acts as controller for the content of the sandbox. All shared
# configuration, variables, and everything that any module or sample may depend
# on should be here. Be careful when declaring shared setup because any kind of
# global setup is evil.

cmake_minimum_required(VERSION 3.14)
project(sandbox)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Configure dependencies below.

include(FetchContent)

# Must be enabled for GIT_PROGRESS to work.
# https://stackoverflow.com/questions/60457301/cmake-fetchcontent-show-download-progress
# It is terribly confusing to see blank screen after running `cmake ..` to
# generate project. Use this flag by default because if it was enabled by
# default i wouldn't have to search for half an hour to figure out what's going
# on under the hood and why there is no progress.
# After enabling the flag in combination with `GIT_PROGRESS TRUE` it is much
# clearer what is happening. Leave it on by default.
set(FETCHCONTENT_QUIET FALSE)

# See why we need this flag: https://github.com/boostorg/cmake/issues/6
# I didn't check whether it works without it.
set(BOOST_ENABLE_CMAKE ON)

FetchContent_Declare(
  boost
  GIT_REPOSITORY https://github.com/boostorg/boost
  # It is recommended to use hash.
  GIT_TAG b6928ae5c92e21a04bbe17a558e6e066dbe632f6 # boost-1.82.0
  # Show progress, requires `FETCHCONTENT_QUIET FALSE`
  # https://stackoverflow.com/questions/60457301/cmake-fetchcontent-show-download-progress
  GIT_PROGRESS TRUE
  # Cloning submodules is slow for me, be selective when adding them.
  #
  # Absolutely make sure at all times to include every submodule under "tools/*"
  # directory in boost. If they are not downloaded there will be an error that
  # boost can't find `BoostRoot.cmake`. I checked with ChatGPT why BoostRoot was
  # missing and it said that BoostRoot.cmake is generated when boost is built.
  # That made me want to build boost manually and I learned that `tools/`
  # directory is empty. I tried to follow this guide to build boost from:
  # `build/_deps/boost-src/`.
  # https://www.boost.org/doc/libs/1_82_0/more/getting_started/windows.html#install-boost-build
  # I realized that all tools are submodules and after adding them, the error
  # that BoostRoot is missing was gone.
  GIT_SUBMODULES "tools/*"
)
FetchContent_MakeAvailable(boost)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# The simplest way I could find to get the current directory name.
function(set_current_dirname var)
  cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME current_dirname)
  set(${var} ${current_dirname} PARENT_SCOPE)
endfunction()

add_subdirectory(modules)
add_subdirectory(samples)
