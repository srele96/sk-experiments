#include <iostream>

// it seems this is what we are doing with header files after preprocessing
int foo();

// multiple declarations? still work?
int foo();

// what if i remove definition? aha, linker complains, which means compiler and
// assembler did their job
//
// int foo() {
//   return 3;
// }

int main() {
  std::cout << foo();

  return 0;
}
