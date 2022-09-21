#include "janitor.h"

#include <utility>

role::Janitor::Janitor(std::string name, std::string last_name)
    : name_{std::move(name)}, last_name_{std::move(last_name)} {}

std::string role::Janitor::Work() {
  return name_ + " " + last_name_ +
         " Sweeps, mops, polishes, and vacuums floors.";
}
