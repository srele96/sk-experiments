#include <fstream>
#include <iostream>
#include <vector>

void dump_list(std::ostream& _ostream, const std::vector<int>& list) {
  _ostream << "List of: ";
  for (auto it = list.begin(); it != list.end(); ++it) {
    _ostream << *it << " ";
  }
}

int main() {
  const std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8};
  dump_list(std::cout, numbers);
  // Attempt to use function that takes std::ostream& to dump the content of
  // the list to different streams.
  // Since the executable will hopefully be in the correct place inside /src
  // directory, i could use /build directory which is listed in .gitignore
  // to output a generated file there since I have no restrictions on where it
  // should be positioned.
  std::ofstream file{"build/numbers.txt"};
  dump_list(file, numbers);
  file.close();
  return 0;
}
