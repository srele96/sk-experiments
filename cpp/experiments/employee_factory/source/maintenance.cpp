#include "maintenance.h"

Maintenance::Maintenance(const std::string& name, const std::string& last_name)
    : name_{name}, last_name_{last_name} {}

std::string Maintenance::Work() {
  return name_ + " " + last_name_ +
         " Installs, repairs, and maintains machinery and mechanical equipment "
         "by completing preventive maintenance.";
}
