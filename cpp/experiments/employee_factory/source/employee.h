#pragma once

#include <string>

class Employee {
 public:
  virtual std::string Work() = 0;
  virtual ~Employee() = default;
};
