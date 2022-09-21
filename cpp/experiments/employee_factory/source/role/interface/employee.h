#pragma once

#include <string>

namespace role {
namespace interface {

class Employee {
 public:
  virtual std::string Work() = 0;
  virtual ~Employee() = default;
};

}  // namespace interface
}  // namespace role
