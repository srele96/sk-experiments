#include "tester.h"

Tester::Tester(const std::string& name, const std::string& last_name)
    : Person{name, last_name} {}

std::string Tester::Work() {
  return name_ + " " + last_name_ + " Ensures quality of manufactured goods.";
}
