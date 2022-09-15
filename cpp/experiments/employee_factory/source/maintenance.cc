#include "maintenance.h"

Maintenance::Maintenance(const std::string& name, const std::string& last_name)
    : Person{name, last_name} {}

std::string Maintenance::Work() {
  return name_ + " " + last_name_ +
         " Installs, repairs, and maintains machinery and mechanical equipment "
         "by completing preventive maintenance.";
}
