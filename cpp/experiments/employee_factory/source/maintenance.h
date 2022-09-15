#pragma once

#include "employee.h"
#include "person.h"

class Maintenance : public Person, public Emplyee {
 public:
  Maintenance(const std::string& name, const std::string& last_name);
  std::string Work();
};
