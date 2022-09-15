#ifndef EMPLOYEE_FACTORY_JANITOR_H
#define EMPLOYEE_FACTORY_JANITOR_H

#include <string>

#include "employee.h"
#include "person.h"

class Janitor : public Person, public Employee {
 public:
  Janitor(const std::string& name, const std::string& last_name);
  std::string Work();
};

#endif
