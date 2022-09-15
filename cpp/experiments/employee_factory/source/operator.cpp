#include "operator.h"

Operator::Operator(const std::string& name, const std::string& last_name)
    : Person{name, last_name} {}

std::string Operator::Work() {
  return name_ + " " + last_name_ +
         " Installs, fixes and operates various types of machinery.";
}
