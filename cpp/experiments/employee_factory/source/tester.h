#pragma once

#include <string>

#include "employee.h"

class Tester : public Employee {
 private:
  std::string name_;
  std::string last_name_;

 public:
  Tester(std::string name, std::string last_name);
  std::string Work();
};
