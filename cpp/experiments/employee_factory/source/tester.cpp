#include "tester.h"

#include <utility>

Tester::Tester(std::string name, std::string last_name)
    : name_{std::move(name)}, last_name_{std::move(last_name)} {}

std::string Tester::Work() {
  return name_ + " " + last_name_ + " Ensures quality of manufactured goods.";
}
