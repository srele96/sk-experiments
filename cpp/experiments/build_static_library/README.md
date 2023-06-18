# C++ build and use the static library on windows

## Specifications

Create a class Point in:

- `Point.hpp`
- `Point.cpp`

Then use it as library from `main.cpp`.

## Findings

```bat
@REM create Point.o
clang++ Point.cpp

@REM create library from object file
ar rvs Point.lib Point.o

@REM link library and compile program
clang++ main.cpp Point.lib -o main
```

## Reference

[stackoverflow - how to create a static library](https://stackoverflow.com/questions/5947067/how-to-create-a-static-library-with-g)
