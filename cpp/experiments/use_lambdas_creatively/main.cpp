#include <functional>
#include <iostream>

int get_whatever() {
  const int whatever{10};
  return whatever;
}

using whatever_t = int (*)();

whatever_t get_whatever_function() {
  return &get_whatever;  // Probably very nasty... Reference to global function.
}

std::function<int()> get_whatever_foo() {
  std::function<int()> foo{[] {
    const int whatever{15};
    return whatever;
  }};

  return foo;
}

whatever_t get_whatever_bar() {
  return [] {
    const int whatever{20};
    return whatever;
  };
}

void use_callback_foo(void (*callback)(int)) {
  const int whatever{25};
  callback(whatever);
}

void use_callback_bar(const std::function<void(int)>& callback) {
  const int whatever{30};
  callback(whatever);
}

void use_callback_baz(const std::function<void(int)>& callback) {
  const int whatever{35};
  callback(whatever);
}

struct callback_baz {
  void operator()(int whatever) { std::cout << whatever << "\n"; }
};

auto curry(const std::function<void(int)>& callback) {
  return [&callback]() {
    return [&callback](int whatever) { callback(whatever); };
  };
}

int main() {
  int (*whatever_ptr)(){&get_whatever};
  std::cout << whatever_ptr() << "\n";

  auto whatever_lambda{[]() {
    const int whatever{5};
    return whatever;
  }};
  std::cout << whatever_lambda() << "\n";

  auto whatever_function{get_whatever_function()};
  std::cout << whatever_function() << "\n";

  std::function<int()> whatever_foo{get_whatever_foo()};
  std::cout << whatever_foo() << "\n";

  std::cout << get_whatever_bar()() << "\n";

  auto whatever_bar{get_whatever_bar()};
  std::cout << whatever_bar() << "\n";

  use_callback_foo([](int whatever) { std::cout << whatever << "\n"; });
  use_callback_bar([](int whatever) { std::cout << whatever << "\n"; });
  use_callback_baz(callback_baz{});

  // Create variable and pass it to curry function, which invokes callback with
  // passed variable. Obscure, but possible and creative.
  const int whatever{40};
  curry([](int value) { std::cout << value << "\n"; })()(whatever);

  return 0;
}
