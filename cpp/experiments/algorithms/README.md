# Algorithms

This experiment groups the C++ implementation of various algorithms.

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
