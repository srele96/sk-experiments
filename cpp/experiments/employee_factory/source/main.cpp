#include <iostream>
#include <memory>

#include "facility.h"
#include "role.h"

int main() {
  facility::Factory thornhil_industries;

  thornhil_industries.Accept(std::make_unique<role::Janitor>("John", "Doe"));
  thornhil_industries.Accept(std::make_unique<role::Janitor>("Moggie", "Girl"));
  thornhil_industries.Accept(std::make_unique<role::Tester>("Rob", "Robinson"));
  thornhil_industries.Accept(std::make_unique<role::Tester>("Kitty", "Woman"));
  thornhil_industries.Accept(
      std::make_unique<role::Maintenance>("Chris", "Crimson"));
  thornhil_industries.Accept(
      std::make_unique<role::Maintenance>("Captain", "Feline"));
  thornhil_industries.Accept(std::make_unique<role::Operator>("Jane", "Doe"));
  thornhil_industries.Accept(
      std::make_unique<role::Operator>("Hindrance", "Man"));

  thornhil_industries.StartWorkHours();

  return 0;
}
