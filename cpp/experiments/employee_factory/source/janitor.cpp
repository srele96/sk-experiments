#include "janitor.h"

Janitor::Janitor(const std::string& name, const std::string& last_name)
    : Person{name, last_name} {}

std::string Janitor::Work() {
  return name_ + " " + last_name_ +
         " Sweeps, mops, polishes, and vacuums floors.";
}
