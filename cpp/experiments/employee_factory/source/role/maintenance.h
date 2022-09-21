#pragma once

#include <string>

#include "employee.h"

namespace role {

class Maintenance : public Employee {
 private:
  std::string name_;
  std::string last_name_;

 public:
  Maintenance(std::string name, std::string last_name);
  std::string Work();
};

}  // namespace role
