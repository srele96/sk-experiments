#include <iostream>

class foo {
 private:
  const int initial_value{10};

 public:
  foo() { std::cout << m_value << " constructor\n"; }
  foo(const foo& other) { std::cout << m_value << " copy constructor\n"; }
  foo(foo&& other) noexcept { std::cout << m_value << " move constructor\n"; }
  foo& operator=(const foo& other) {
    std::cout << m_value << " copy assignment\n";
    if (this == &other) {
      return *this;
    }
    return *this;
  }
  foo& operator=(foo&& other) noexcept {
    std::cout << m_value << " move assignment\n";
    return *this;
  }
  ~foo() { std::cout << m_value << " destructor\n"; }

  int m_value{initial_value};
};

void observe_lambda_capture_behavior() {
  foo first_foo;

  // const copies by default prevent unintended mutation
  // auto observe_behavior_by_value = [=]() {  // doesn't compile
  //   constexpr int new_value{15};
  //   first_foo.m_value = new_value;
  //   std::cout << first_foo.m_value << " - Lambda by copy!\n ";
  // };

  // Does it invoke copy assignment and related semantics? - Yes.
  auto observe_behavior_by_value = [=]() mutable {  // works, can mutate
    constexpr int new_value{15};
    first_foo.m_value = new_value;
    std::cout << first_foo.m_value << " - Lambda by copy!\n";
  };

  observe_behavior_by_value();

  // Looks like mutable is only for variables captured by value.
  auto observe_behavior_by_reference = [&]() {
    constexpr int new_value{20};  // Differentiate because of destructor outside
    first_foo.m_value = new_value;
    std::cout << first_foo.m_value << " - Lambda by reference!\n";
  };

  observe_behavior_by_reference();
  std::cout << first_foo.m_value << " - After lambda by reference!\n";
}

int main() {
  observe_lambda_capture_behavior();

  return 0;
}
