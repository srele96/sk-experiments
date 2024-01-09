# Algorithms

This experiment groups the C++ implementation of various algorithms.

## 30.12.2023 - 01.14.2024 Solve algorithmic problems and ride a bike

I ride a bike to improve blood circulation to improve my problem-solving performance. While riding a bike I think about algorithmic problems and how to solve them.

## Books

- ["Algorithmic Problem Solving" by Roland Backhouse](https://books.google.rs/books?id=84VZLWMnKrQC&printsec=frontcover&redir_esc=y#v=onepage&q&f=false)

## How to run

Windows operating system.

Use `cp.bat` to run programs using flags for competitive programming.

```cmd
cp graphs
```

Use `run.bat` to run programs using strict flags.

```cmd
run graphs
```

## Improve autocomplete

Make sure to use clang-tidy extension with Visual Studio code.

Add the following to `settings.json` to tell clang-tidy where to find includes for gtest. Adjust absolute path to the one on your machine.

```json
{
  "clang-tidy.compilerArgs": [
    "-IC:/Users/Srecko/Documents/MyProjects/Private/container-sk-experiments/sk-experiments/cpp/experiments/algorithms/build/vcpkg_installed/x64-mingw-dynamic/include"
  ]
}
```

## How to run tests

Generate project:

The flag `-DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic` is required to avoid linking errors because I don't know why without that flag linker complains.

It seems that `x64-windows` configuration relies on `msvc` compiler and here I don't use any specific compiler all the time. I switch between `g++` and `clang++`... I didn't test whether `x64-windows` configuration works with `msvc` compiler.

```powershell
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:\src\vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic
```

Build tests:

```powershell
cmake --build build
```
