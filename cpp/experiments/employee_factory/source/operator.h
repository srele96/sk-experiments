#pragma once

#include <string>

#include "employee.h"

class Operator : public Employee {
 private:
  std::string name_;
  std::string last_name_;

 public:
  Operator(std::string name, std::string last_name);
  std::string Work();
};
