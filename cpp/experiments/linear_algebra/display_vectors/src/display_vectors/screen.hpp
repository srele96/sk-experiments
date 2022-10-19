#ifndef DISPLAY_VECTORS_SCREEN_HPP
#define DISPLAY_VECTORS_SCREEN_HPP

#include <stdexcept>
#include <vector>

namespace display_vectors {

// https://stackoverflow.com/questions/482745/namespaces-for-enum-types-best-practices
// The enum class prevents leaking enum properties outside.
enum class dimension { _1d, _2d, _3d };

std::vector<std::vector<char>> create_screen(dimension space);

}  // namespace display_vectors

#endif  // DISPLAY_VECTORS_SCREEN_HPP
