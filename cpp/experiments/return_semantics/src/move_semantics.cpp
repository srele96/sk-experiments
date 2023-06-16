#include <iostream>
#include <string>
#include <utility>

class Foo {
 public:
  Foo() { std::cout << "ctor\n"; }
  explicit Foo(std::string value) : value_{std::move(value)} {}
  Foo(const Foo& other) { std::cout << "copy ctor\n"; }
  Foo(Foo&& other) { std::cout << "move ctor\n"; }
  Foo& operator=(const Foo& other) {
    std::cout << "copy assignment\n";
    return *this;
  }
  Foo& operator=(Foo&& other) {
    std::cout << "move assignment\n";
    return *this;
  }
  ~Foo() { std::cout << "dtor\n"; }

  std::string value_;
};

Foo get_foo() { return Foo{}; }

Foo get_modified_foo() {
  Foo foo;
  foo.value_ = "modified";  // Prevent optimization or whatever
  return foo;               // Why move constructor?
}

Foo get_initialized_and_returned_foo() {
  Foo foo{"initialized"};
  return foo;
}

Foo get_returned_foo() { return Foo{"returned"}; }

template <typename T>
void run_example(const std::string& function_call_signature,
                 const T& function) {
  std::cout << "before " << function_call_signature << "\n";
  function();
  std::cout << "after " << function_call_signature << "\n";
  std::cout << "----\n";
}

int main() {
  run_example("get_foo()", get_foo);
  run_example("get_modified_foo()", get_modified_foo);
  run_example("get_initialized_and_returned_foo()",
              get_initialized_and_returned_foo);
  run_example("get_returned_foo()", get_returned_foo);

  return 0;
}
