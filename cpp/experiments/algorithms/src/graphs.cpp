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

struct children_indexes {
  int left;
  int right;
};

children_indexes get_children_indexes(int index) {
  return children_indexes{2 * index + 1, 2 * index + 2};
}

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
  const int index = 1;
  data_structure::children_indexes children_indexes =
      data_structure::get_children_indexes(index);

  std::cout << "Child " << children_indexes.left << " , "
            << children_indexes.right << '\n';

  graphs::print_connected_vertices();

  return 0;
}
