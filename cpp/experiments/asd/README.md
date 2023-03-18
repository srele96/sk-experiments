# asd

## Setup dependencies

Requirements:

- `clang` - C compiler.
- `llvm-ar` - Tool to create static library, check `BuildMongooseLib` scripts.

1. Run `.\SetupMongoose`

The script `SetupMongoose` will create directories, files, download dependencies and build the static library.

## Build project

Requiremenets:

- Using [MSYS2](https://www.msys2.org/docs/cmake/) download [CMake](https://cmake.org/). In short, you simply need MSYS2 on windows if you don't know what to do.

1. Create build directory `mkdir build`
2. Enter build directory `cd build`
3. Initialize CMake `cmake ..`
4. Build project using CMake `cmake --build .`
5. Search in the console for executable location to run it
