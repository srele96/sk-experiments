#ifndef EMPLOYEE_FACTORY_OPERATOR_H
#define EMPLOYEE_FACTORY_OPERATOR_H

#include <string>

#include "employee.h"
#include "person.h"

class Operator : public Person, public Employee {
 public:
  Operator(const std::string& name, const std::string& last_name);
  std::string Work();
};

#endif
