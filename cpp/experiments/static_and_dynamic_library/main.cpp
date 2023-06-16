#include <iostream>

#include "whatever.h"

int main() {
  std::cout << "Give me int: " << whatever::give_me_int() << "\n"
            << "Give me string: " << whatever::give_me_string() << "\n";

  return 0;
}
