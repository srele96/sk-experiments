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

Foo return_by_value() { return Foo{3}; }

}  // namespace initialization_types

// ----------------------------------------------------------------------------
// Why do we need copy constructor?
//  - https://en.wikipedia.org/wiki/Copy_constructor_(C%2B%2B)
//
// We have to define constructor/copy/move/destructor semantics when we own a
// non trivial resource like:
//  - file handle
//  - pointer
//  - socket
//
// Why?
//
// Compiler defines a default semantic for trivial values, however when we use a
// resource like socket, how can a compiler know how to copy/move/destroy it?
// Usually when we own a resource, for example a socket, we want to define how
// to copy/move/destroy it as well. Why is that? RAII - Resource Acquisition Is
// Initialization. As Bjarne Stroustrup said, we are good at taking ownership
// but we are not good at cleaning up. We often forget to clean up, an error may
// prevent cleanup or an early return. However when we define copy/move/destroy
// at the moment of acquisition we save ourselves from these cases.
// ----------------------------------------------------------------------------

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

  initialization_types::return_by_value();

  return 0;
}
