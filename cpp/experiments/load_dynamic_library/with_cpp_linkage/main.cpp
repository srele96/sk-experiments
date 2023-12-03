#include <iostream>

#include "Library/Library.h"

int main() {
  {
    constexpr int first{3};
    constexpr int second{5};
    std::cout << library_add(first, second) << "\n";
  }

  {
    constexpr int first{5};
    constexpr int second{5};
    std::cout << Library::Add(first, second) << "\n";
  }

  {
    const std::string str{"Library!"};
    Library::X holder{str};
    std::cout << holder.str() << "\n";
    const std::string new_str{"Change!"};
    holder.str(new_str);
    std::cout << holder.str();
  }

  return 0;
}
