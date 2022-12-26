#include <array>
#include <iostream>

// implement heap
// what if i want to represent a heap using graph?
// implement heap using
//  - matrix
//  - tree
//  - array

namespace data_structure {

class heap {
  // store data using array, matrix or array

  // how should heap work?

  // operations
  // insert
  // delete
  // peek
  // extract
  // decrease_key
  // increase_key
};

};  // namespace data_structure

namespace graphs {

void print_connected_vertices() {
  const std::size_t side_length = 5;
  std::array<std::array<int, side_length>, side_length> graph{{
      {0, 1, 1, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 0, 1},
      {0, 1, 0, 0, 1},
      {0, 0, 1, 1, 0},
  }};

  for (std::size_t i = 0; i != graph.size(); ++i) {
    for (std::size_t j = 0; j != graph.at(i).size(); ++j) {
      if (graph.at(i).at(j) != 0) {
        std::cout << i << " - " << j << '\n';
      }
    }
  }
}

};  // namespace graphs

int main() {
  graphs::print_connected_vertices();

  return 0;
}
