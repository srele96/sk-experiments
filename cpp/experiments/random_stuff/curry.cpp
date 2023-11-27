#include <iostream>

int main() {
  // Many programming patterns are transferable from one language to other. I
  // learned curring using JavaScript and it's applicable in C++. I understood
  // that Bjarne wanted C++ to support useful programming patterns. In his time
  // there was no Object Oriented Programming language as efficient as C.

  // Can store state in the object and use it in the operator() function.
  struct Curry {
    // Only struct Curry knows about struct C because only it uses it.
    struct C {
      // Only struct C knows about struct B because only it uses it.
      struct B {
        // Only struct B knows about struct A because only it uses it.
        struct A {
          void operator()(int x, int y) const {
            std::cout << "A: (" << x << ", " << y << ")\n";
          }
        };

        A operator()(int x, int y) const {
          std::cout << "B: (" << x << ", " << y << ")\n";
          return A{};
        }
      };

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
  Curry::C::B b{c(11, 12)};
  Curry::C::B::A a{b(13, 14)};
  a(15, 16);

  return 0;
}
