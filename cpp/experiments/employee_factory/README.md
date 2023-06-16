# Employee Factory

Implementation of Employee Factory from [Employee Factory Design Document](./DESIGN_DOCUMENT.md)

## My goals with this sample

This sample attempts to achieve a few goals:

- Use as many best practises as possible to implement sample real life scenario.
- Simulate somewhat real sample of building C++ projects. We achieve that using CMake build system.
- Split program using multiple files. Build system provides us to split program in modular way.
- Use design document to define solution that we are going to implement. Well defined solution using english description eases the implementation.
- Use solution that is as semantic as possible. Mistakes are inevitable and I am just starting out. I am trying to mitigate beginner mistakes by doing proportional amount of research.

If we consider all goals and look at implementation we can conclude that the whole sample is overengineered. However, I did it on purpose.

## Build steps

Steps to build the project.

### Step 1

Make sure you are in root directory `employee_factory`.

### Step 2

Create build directory

```txt
mkdir build
```

### Step 3

Go to build directory.

```txt
cd build
```

### Step 4

Generate whatever CMake needs.

```txt
cmake ..
```

### Step 5

Build the project with CMake.

```txt
cmake --build .
```

### Step 6

Run the executable.

```txt
./employee_factory
```
