#pragma once

#include "employee.h"
#include "person.h"

class Janitor : public Person, public Emplyee {
 public:
  Janitor(const std::string& name, const std::string& last_name);
};