#ifndef EMPLOYEE_FACTORY_EMPLOYEE_H
#define EMPLOYEE_FACTORY_EMPLOYEE_H

#include <string>

class Emplyee {
 public:
  virtual std::string Work() = 0;
  virtual ~Emplyee() = default;
};

#endif
