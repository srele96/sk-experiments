#ifndef EMPLOYEE_FACTORY_OPERATOR_H
#define EMPLOYEE_FACTORY_OPERATOR_H

#include "employee.h"
#include "person.h"

class Operator : public Person, public Emplyee {
 public:
  Operator(const std::string& name, const std::string& last_name);
  std::string Work();
};

#endif EMPLOYEE_FACTORY_OPERATOR_H
