#include "factory.h"

#include <iostream>

void facility::Factory::Accept(std::unique_ptr<role::Employee>&& employee) {
  employees.push_back(std::move(employee));
}

void facility::Factory::StartWorkHours() {
  for (const auto& employee : employees) {
    std::cout << employee->Work() << "\n";
  }
}
