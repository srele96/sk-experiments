# Employee Factory

Design document for the Employee Factory project. _[How to Write a Design Document](https://people.eecs.berkeley.edu/~kubitron/courses/cs162-F06/design.html)_

## The problem

The factory employs many employees. Employees have one of these roles: cleaning, checking product quality and testing samples, maintaining equipment, operating forklifts, and aligning workpieces. Each employee has different job responsibilities, but they all work during work hours.

## Solution

We will implement the Factory facility. Such a facility will hold all employees and start work hours once everyone is ready.

The facility doesn't need to know about the Employee's role. Every employee at the facility is expected to work. What he does is defined by his role. The facility may have many janitors with different names. They have different names but they do the same work.

Class Person declares shared data for all Employees. Their name and last name.

Class Employee is an interface that declares what employee does.

Classes Janitor, Tester, Maintenance and Operator define Employees behavior. They are essentially People, therefore they share those properties through inheritance.

## Pseudo code

```txt
The class factory serves as a facility where employees are working. When
working hours start, we expect all employees to work.

Factory
 public:
  Accept(employee)
  StartWorkHours()
    foreach employee in employees
      print(employee.work())

 private:
  // check google naming conventions
  employees_

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The class Person is root class that defines properties every person should have.

class Person:
 protected:
  name_
  last_name_

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The class Employee is an interface that enforces Employee to define the way he
works.

Employee:
 public:
  virtual Work() = 0

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The inheritance model is as follows:

Janitor     : Person, Employee
Tester      : Person, Employee
Maintenance : Person, Employee
Operator    : Person, Employee

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Definitions of how each employee role works:

Janitor::Work()
  return name + " " + last_name_ + " Sweeps, mops, polishes, and vacuums floors."

Tester::Work()
  return name_ + " " + last_name_+ " Ensures quality of manufactured goods."

Maintenance::Work()
  return name_ + " " + last_name + " Installs, repairs, and maintains machinery and mechanical equipment by completing preventive maintenance."

Operator::Work()
  return name_ + " " + last_name + " Installs, fixes and operates various types of machinery."
```
