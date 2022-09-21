#include "maintenance.h"

#include <utility>

Maintenance::Maintenance(std::string name, std::string last_name)
    : name_{std::move(name)}, last_name_{std::move(last_name)} {}

std::string Maintenance::Work() {
  return name_ + " " + last_name_ +
         " Installs, repairs, and maintains machinery and mechanical equipment "
         "by completing preventive maintenance.";
}
