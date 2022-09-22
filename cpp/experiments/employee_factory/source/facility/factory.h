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
  void Accept(std::unique_ptr<role::Employee>&& employee);
  void StartWorkHours();
};

}  // namespace facility
