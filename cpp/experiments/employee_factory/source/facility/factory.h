#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "../role.h"

namespace facility {

class Factory {
 private:
  std::vector<std::unique_ptr<role::Employee>> employees{};

 public:
  // http://scottmeyers.blogspot.com/2014/07/should-move-only-types-ever-be-passed.html
  void Accept(std::unique_ptr<role::Employee>&& employee);
  void StartWorkHours();
};

}  // namespace facility
