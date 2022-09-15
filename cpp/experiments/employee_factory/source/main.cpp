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

  std::cout << "---------------------------------------\n"
            << "Verify that employee roles are working.\n"
            << "---------------------------------------\n"
            << john.Work() << "\n"
            << rob.Work() << "\n"
            << chris.Work() << "\n"
            << jane.Work() << "\n";
}
