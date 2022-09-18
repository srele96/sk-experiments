#pragma once

#include <string>

#include "employee.h"
#include "person.h"

class Janitor : public Person, public Employee {
 public:
  Janitor(const std::string& name, const std::string& last_name);
  std::string Work();
};
