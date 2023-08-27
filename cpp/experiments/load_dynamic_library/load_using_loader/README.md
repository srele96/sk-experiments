# Load using loader

I created a terrible importer that loads function pointers from a dynamic library! Hooray for the terrible code!

## Write library loader

Per my current bloody understanding!

Library loader is a header file compiled as static library that contains two main parts:

1. `init` function that loads the library and initializes the function pointers. It also provides the type declarations.
2. `free` function which unloads the library and releases all acquired resources.

In other terms, it is a wrapper around the code in [`main.cpp`](./main.cpp) so the user doesn't need to write those manually.

## Build and run

Build dynamic library:

```powershell
clang++ -fPIC -shared Library/Library.cpp -o Library.dll
```

Compile the executable to use the functional loading style:

```powershell
clang++ -std=c++17 main.cpp -o main.exe
```

Run the executable to verify that it runs:

```powershell
./main.exe
```

Compile the executable to use the class loading style:

```powershell
clang++ -std=c++17 main.cpp -o main.exe -DUSE_CLASS
```

Run the executable to verify that it runs:

```powershell
./main.exe
```
