#pragma once

#include <string>

#include "employee.h"
#include "person.h"

class Tester : public Person, public Employee {
 public:
  Tester(const std::string& name, const std::string& last_name);
  std::string Work();
};
