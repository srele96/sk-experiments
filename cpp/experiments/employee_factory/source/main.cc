#include <iostream>

#include "janitor.h"
#include "maintenance.h"
#include "operator.h"
#include "tester.h"

int main() {
  Janitor john{"John", "Doe"};
  Tester rob{"Rob", "Robinson"};
  Maintenance chris{"Chris", "Crimson"};
  Operator jane{"Jane", "Doe"};

  std::cout << "---------------------------------------\n";
  std::cout << "Verify that employee roles are working.\n";
  std::cout << "---------------------------------------\n";
  std::cout << john.Work() << "\n";
  std::cout << rob.Work() << "\n";
  std::cout << chris.Work() << "\n";
  std::cout << jane.Work() << "\n";
}
