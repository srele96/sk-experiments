#include "person.h"

Person::Person(const std::string& name, const std::string& last_name)
    : name_{name}, last_name_{last_name} {}

std::string Person::name() const { return name_; }

std::string Person::last_name() const { return last_name_; }
