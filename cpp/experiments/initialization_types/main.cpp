#include <iostream>

namespace initialization_types {

const int default_value = 0;

class Foo {
 private:
  int _value;

 public:
  Foo() : _value{default_value} { std::cout << "ctor - " << _value << '\n'; }
  // Why do I need explicit here?
  Foo(int value) : _value{value} { std::cout << "ctor - " << _value << '\n'; }
};

}  // namespace initialization_types

int main() {
  using Foo = initialization_types::Foo;
  Foo foo_one;

  return 0;
}
