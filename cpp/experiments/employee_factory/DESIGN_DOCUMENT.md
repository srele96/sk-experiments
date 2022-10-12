# Employee Factory

Design document for the Employee Factory project. _[How to Write a Design Document](https://people.eecs.berkeley.edu/~kubitron/courses/cs162-F06/design.html)_

## The problem

The factory employs many employees. Employees have one of these roles: cleaning, checking product quality and testing samples, maintaining equipment, operating forklifts, and aligning workpieces. Each employee has different job responsibilities, but they all work during work hours.

## Solution

We will implement the Factory facility. Such a facility will hold all employees and start work hours once everyone is ready.

The facility doesn't need to know about the Employee's role. Every employee at the facility is expected to work. What he does is defined by his role. The facility may have many janitors with different names. They have different property values but they do the same work.

Class Employee is an interface that declares what an employee does.

Classes Janitor, Tester, Maintenance, and Operator define Employee's behavior.

## Solution architecture

A line ending with forward slash `/` is a directory. Otherwise, it is implementation file.

```txt
main
facility/
  factory
role/
  employee
  janitor
  tester
  maintenance
  operator
```

## Pseudo code

```txt
The class factory serves as a facility where employees are working. When
working hours start, we expect all employees to work.

Factory
 public:
  Accept(employee)
  StartWorkHours()
    foreach employee in employees
      print(employee.Work())

 private:
  employees

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The class Employee is an interface that enforces Employee to define the way he
works.

Employee:
 public:
  virtual Work() = 0

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Janitor : Employee
  public:
    Work():
      return name + " " + last_name_ +
        " Sweeps, mops, polishes, and vacuums floors."

  private:
    name_
    last_name_

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Tester : Employee
  public:
    Work():
      return name_ + " " + last_name_+
        " Ensures quality of manufactured goods."

  private:
    name_
    last_name_

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Maintenance : Employee
  public:
    Work():
      return name_ + " " + last_name +
        " Installs, repairs, and maintains machinery and mechanical " +
        "equipment by completing preventive maintenance."

  private:
    name_
    last_name_

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Operator : Employee
  public:
    Work()
      return name_ + " " + last_name +
        " Installs, fixes and operates various types of machinery."

  private:
    name_
    last_name_
```
