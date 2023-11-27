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

// Recursion practise. I spotted a chance to write a recursive function even
// though it is much more robust than the formula. I noticed that the indexes of
// left and right child for N-th node start from the right child's index of the
// N-1-th node. I wanted to write a recursive function for that.
children_indexes get_children_indexes_recursively(int index) noexcept {
  // I didn't learn error handling yet so you better pass this function a
  // positive integer.
  if (index == 0) {
    return children_indexes{1, 2};
  }

  const children_indexes previous = get_children_indexes_recursively(index - 1);
  const int left_child = 1;
  const int right_child = 2;

  return children_indexes{previous.right + left_child,
                          previous.right + right_child};
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
  const int index = 2;
  data_structure::children_indexes children_indexes =
      data_structure::get_children_indexes(index);
  data_structure::children_indexes children_indexes_recursively =
      data_structure::get_children_indexes_recursively(index);

  std::cout << "Child " << children_indexes.left << " , "
            << children_indexes.right << '\n';
  std::cout << "Child indexes recursively " << children_indexes_recursively.left
            << " , " << children_indexes_recursively.right << '\n';

  graphs::print_connected_vertices();

  return 0;
}
