#include <iostream>

int main() {
  // Many programming patterns are transferable from one language to other. I
  // learned curring using JavaScript and it's applicable in C++. I understood
  // that Bjarne wanted C++ to support useful programming patterns. In his time
  // there was no Object Oriented Programming language as efficient as C.

  struct Curry {
    // Can store state in the object and use it in the operator() function.

    struct A {
      void operator()(int x, int y) const {
        std::cout << "A: (" << x << ", " << y << ")\n";
      }
    };

    struct B {
      A operator()(int x, int y) const {
        std::cout << "B: (" << x << ", " << y << ")\n";
        return A{};
      }
    };

    struct C {
      B operator()(int x, int y) const {
        std::cout << "C: (" << x << ", " << y << ")\n";
        return B{};
      }
    };

    C operator()(int x, int y) const {
      std::cout << "Curry: (" << x << ", " << y << ")\n";
      return C{};
    }
  };

  Curry{}(1, 2)(3, 4)(5, 6)(7, 8);

  Curry::C c{Curry{}(9, 10)};
  Curry::B b{c(11, 12)};
  Curry::A a{b(13, 14)};
  a(15, 16);

  return 0;
}
