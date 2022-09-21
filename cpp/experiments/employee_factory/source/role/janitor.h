#pragma once

#include <string>

#include "interface.h"

namespace role {

class Janitor : public interface::Employee {
 private:
  std::string name_;
  std::string last_name_;

 public:
  Janitor(std::string name, std::string last_name);
  std::string Work();
};

}  // namespace role
