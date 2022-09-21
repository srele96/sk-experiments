#pragma once

#include <string>

#include "employee.h"

class Maintenance : public Employee {
 private:
  std::string name_;
  std::string last_name_;

 public:
  Maintenance(std::string name, std::string last_name);
  std::string Work();
};
