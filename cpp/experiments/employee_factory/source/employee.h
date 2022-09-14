#pragma once

#include <string>

class Emplyee {
 public:
  virtual std::string Work() = 0;
  virtual ~Emplyee() = default;
};
