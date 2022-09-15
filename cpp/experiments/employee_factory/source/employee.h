#ifndef EMPLOYEE_FACTORY_EMPLOYEE_H
#define EMPLOYEE_FACTORY_EMPLOYEE_H

#include <string>

class Employee {
 public:
  virtual std::string Work() = 0;
  virtual ~Employee() = default;
};

#endif
