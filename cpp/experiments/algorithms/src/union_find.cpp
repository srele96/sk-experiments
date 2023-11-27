#include <algorithm>
#include <iostream>
#include <vector>

namespace argument {

struct operand {
  int first;
  int second;
};

}  // namespace argument

namespace data_structure {

class union_find {
 public:
  int find(int vertex);
  void unite(argument::operand operand);

 private:
  void link_first_to_second(argument::operand operand);

  std::vector<int> link_;
  std::vector<int> size_;
};

}  // namespace data_structure

int data_structure::union_find::find(int vertex) {
  while (vertex != link_.at(vertex)) {
    vertex = link_.at(vertex);
  }

  return vertex;
}

void data_structure::union_find::unite(argument::operand operand) {
  int first_representative = find(operand.first);
  int second_representative = find(operand.second);

  if (size_.at(operand.first) < size_.at(operand.second)) {
    const argument::operand link_order{first_representative,
                                       second_representative};
    link_first_to_second(link_order);
  } else {
    const argument::operand link_order{second_representative,
                                       first_representative};
    link_first_to_second(link_order);
  }
}

void data_structure::union_find::link_first_to_second(
    argument::operand operand) {
  link_.at(operand.first) = link_.at(operand.second);
  size_.at(operand.second) += size_.at(operand.first);
}

int main() {
  data_structure::union_find union_find;

  return 0;
}
