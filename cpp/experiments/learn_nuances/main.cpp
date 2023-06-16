#include <iostream>

// Why does single argument constructor need to be explicit?

void what_is_the_difference() {
  const int data = 5;
  std::cout << data << '\n';  // single quotes
  std::cout << data << "\n";  // double quotes
}

class container {
 public:
  int _value;
  container(int value) : _value{value} {}
};

int main() {
  const int data = 10;
  // Do I need to use `new` to use a pointer?
  container data_source{data};
  container* data_source_ptr = &data_source;

  std::cout << sizeof(data_source) << ", " << sizeof(*data_source_ptr) << '\n';

  std::cout << data_source._value << '\n';

  // Value stored to 'data_source_ptr' during its initialization is never
  // readclang-tidy(clang-analyzer-deadcode.DeadStores)
  // Does this get rid of it?
  std::cout << data_source_ptr->_value << '\n';

  what_is_the_difference();

  return 0;
}
