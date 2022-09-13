# Employee Factory

Design document for the Employee Factory project. _[How to Write a Design Document](https://people.eecs.berkeley.edu/~kubitron/courses/cs162-F06/design.html)_

## The problem

The factory employs many employees. Employees have one of these roles: cleaning, checking product quality and testing samples, maintaining equipment, operating forklifts, and aligning workpieces. Each employee has different job responsibilities, but they all work during work hours.

## Solution

We will implement the Factory facility. Such a facility will hold all employees and start work hours once everyone is ready.

The facility doesn't need to know about the Employee's role. Every employee at the facility is expected to work. What he does is defined by his role. The facility may have many janitors with different names. They have different names but they do the same work.

Employee declares employees' properties and general interface for roles. Each role is responsible to define what it does.

## Pseudo code

```txt
The class factory serves as a facility where employees are working. When
working hours start, we expect all employees to work.

Factory
  Accept(employee)
  StartWorkHours()
    foreach employee in employees
      employee.work()

 private:
  // check google naming conventions
  employees_

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The class Employee is an interface that defines employees' properties and
enforces Employee to define the way he works.

Employee:
 protected:
   name_
   last_name_
 public:
  virtual Work() = 0

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The inheritance model is as follows:

Janitor     : Employee
Tester      : Employee
Maintenance : Employee
Operator    : Employee

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Definitions of how each employee role works:

Janitor::Work()
  print(name + last_name_ + "Sweeps, mops, polishes, and vacuums floors.")

Tester::Work()
  print(name_ + last_name_+ "Ensures quality of manufactured goods.")

Maintenance::Work()
  print(name_ + last_name + "Installs, repairs, and maintains machinery and mechanical equipment by completing preventive maintenance.")

Operator::Work()
  print(name_ + last_name + "Installs, fixes and operates various types of machinery.")
```
