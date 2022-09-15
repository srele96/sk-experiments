#ifndef EMPLOYEE_FACTORY_TESTER_H
#define EMPLOYEE_FACTORY_TESTER_H

#include "employee.h"
#include "person.h"

class Tester : public Person, public Emplyee {
 public:
  Tester(const std::string& name, const std::string& last_name);
  std::string Work();
};

#endif
