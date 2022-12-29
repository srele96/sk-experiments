#include <iostream>

namespace initialization_types {

const int default_value = 0;

class Foo {
 private:
  int _value;

 public:
  Foo() : _value{default_value} {
    std::cout << "default ctor - " << _value << '\n';
  }
  // Why do I need explicit here?
  Foo(int value) : _value{value} { std::cout << "ctor - " << _value << '\n'; }
  // Does copy initialization syntax invoke copy constructor?
  Foo(const Foo& other) : _value(other._value) {
    std::cout << "copy ctor - " << _value << '\n';
  }
};

}  // namespace initialization_types

int main() {
  using Foo = initialization_types::Foo;
  Foo foo_one;       // default
  Foo foo_two{};     // default
  Foo foo_three{3};  // with parameter
  // What is the benefit of the initialization syntax? Why is it better?
  Foo foo_four = Foo(4);
  foo_four = Foo{2};
  // Copy constructor is invoked when the type is declared first. That is
  // construction. Therefore we need copy constructor.
  Foo foo_five = foo_three;

  return 0;
}
