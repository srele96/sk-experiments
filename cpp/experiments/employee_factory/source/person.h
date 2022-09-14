#pragma once

#include <string>

class Person {
 protected:
  std::string name_;
  std::string last_name_;

 public:
  Person(const std::string& name, const std::string& last_name);
  std::string name() const;
  std::string last_name() const;
  virtual ~Person() = default;
};
