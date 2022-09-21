#include "../tester.h"

#include <utility>

role::Tester::Tester(std::string name, std::string last_name)
    : name_{std::move(name)}, last_name_{std::move(last_name)} {}

std::string role::Tester::Work() {
  return name_ + " " + last_name_ + " Ensures quality of manufactured goods.";
}
