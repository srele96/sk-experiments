#include "../operator.h"

#include <utility>

role::Operator::Operator(std::string name, std::string last_name)
    : name_{std::move(name)}, last_name_{std::move(last_name)} {}

std::string role::Operator::Work() {
  return name_ + " " + last_name_ +
         " Installs, fixes and operates various types of machinery.";
}
