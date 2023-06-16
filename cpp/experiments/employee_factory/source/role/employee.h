#pragma once

#include <string>

namespace role {

class Employee {
 public:
  virtual std::string Work() = 0;
  virtual ~Employee() = default;
};

}  // namespace role
