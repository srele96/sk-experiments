#ifndef EMPLOYEE_FACTORY_MAINTENANCE_H
#define EMPLOYEE_FACTORY_MAINTENANCE_H

#include "employee.h"
#include "person.h"

class Maintenance : public Person, public Emplyee {
 public:
  Maintenance(const std::string& name, const std::string& last_name);
  std::string Work();
};

#endif
