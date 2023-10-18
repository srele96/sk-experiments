set_current_dirname(CURRENT_DIRECTORY_NAME)

project(
  ${CURRENT_DIRECTORY_NAME}
  LANGUAGES CXX
  VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 17)
# I tried compiling with clang, but it failed with the following error:
#
# vcpkg_installed/x64-mingw-static/lib/libboost_program_options.a(options_description.o): duplicate section `.rdata$_ZTSSt9exception[_ZTSSt9exception]' has different size
#
# It is most likely because vcpkg builds boost with mingw due to `-DVCPKG_TARGET_TRIPLET=x64-mingw-static` triplet.
set(CMAKE_CXX_COMPILER g++)

add_executable(
  ${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${Boost_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  Boost::program_options
)

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
