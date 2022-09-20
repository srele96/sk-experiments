#pragma once

#include <string>

#include "employee.h"

class Tester : public Employee {
 private:
  std::string name_;
  std::string last_name_;

 public:
  Tester(const std::string& name, const std::string& last_name);
  std::string Work();
};
