#include <iostream>
#include <string>
#include <unordered_map>

namespace solution {

// Pseudo-Code for procedure
//
// Max-Digram-Distance(string):
//
// initiate max distance to non existant distance
// create map of indices of first occurence of each digram
// for each digram
//  if index of first character of digram is saved
//    if max distance is initialized
//      calculate distance from current digram to first matching digram
//      if distance is larger than max distance
//        save distance as max distance
//    else
//      initialize max distance
//  else
//    save digram
// return max distance

std::string::difference_type calcualte_max_digram_distance(
    const std::string &s) {
  constexpr std::string::difference_type not_found{-1};
  std::string::difference_type max_distance{not_found};
  std::unordered_map<std::string, std::string::difference_type>
      index_of_first_digram_occurence;

  for (auto it{s.begin()}; it != s.end(); ++it) {
    std::string::difference_type index{std::distance(s.begin(), it)};
    const std::string::size_type two_characters{2};
    const std::string digram{s.substr(index, two_characters)};

    if (index_of_first_digram_occurence.contains(digram)) {
      std::string::difference_type current_distance{
          index - index_of_first_digram_occurence[digram]};
      if (max_distance == not_found) {
        max_distance = current_distance;
      } else {
        if (current_distance > max_distance) {
          max_distance = current_distance;
        }
      }
    } else {
      index_of_first_digram_occurence[digram] = index;
    }
  }

  return max_distance;
}

}  // namespace solution

int main() {
  std::cout << solution::calcualte_max_digram_distance("abab") << "\n"
            << solution::calcualte_max_digram_distance("ababab") << "\n"
            << solution::calcualte_max_digram_distance("abebabebebab") << "\n"
            << solution::calcualte_max_digram_distance("codility");

  return 0;
}
