#pragma once

#include <string>

#include "employee.h"
#include "person.h"

class Maintenance : public Person, public Employee {
 public:
  Maintenance(const std::string& name, const std::string& last_name);
  std::string Work();
};
