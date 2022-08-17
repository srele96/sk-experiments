# Building with CMake

Building a basic project structure using CMakeLists.txt.

## Description

Using base structure:

```txt
building-with-cmake/
building-with-cmake/.gitignore
building-with-cmake/README.md

building-with-cmake/CMakeLists.txt
building-with-cmake/source
building-with-cmake/source/CMakeLists.txt
building-with-cmake/source/main.cpp
```

## Goals

Build and run the code.

## Build steps

I created this sample on windows machine. I think that is relevant information.

### When first opening the directory

Run the steps in the following order:

```bat
@REM this is a comment

@REM create directory
mkdir build

@REM go to directory
cd build

@REM setup the project
cmake ..

@REM build the program
cmake --build .

@REM run the program
Debug\building-with-cmake
```

### After we create the build directory

Run the following:

```bat
@REM build the program, probably after code change
cmake --build .

@REM run the program
Debug\building-with-cmake
```

Alternatively, we may have to run one more step. Probably if we
change CMakeLists. I am not sure about that.

```bat
@REM setup the project
cmake ..

@REM build the program
cmake --build .

@REM run the program
Debug\building-with-cmake
```
