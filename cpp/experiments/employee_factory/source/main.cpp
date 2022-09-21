#include <iostream>

#include "role.h"

int main() {
  role::Janitor john{"John", "Doe"};
  role::Tester rob{"Rob", "Robinson"};
  role::Maintenance chris{"Chris", "Crimson"};
  role::Operator jane{"Jane", "Doe"};

  std::cout << "---------------------------------------\n"
            << "Verify that employee roles are working.\n"
            << "---------------------------------------\n"
            << john.Work() << "\n"
            << rob.Work() << "\n"
            << chris.Work() << "\n"
            << jane.Work() << "\n";
}
