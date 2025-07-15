# Random stuff

A collection of random stuff that I did on the algorithms branch because I didn't feel like branching off from it.

## Generate code

Clang flags to see the compiler generated code, useful to see generated template metaprogramming code.

```PowerShell
-Xclang -ast-print -fsyntax-only
```

For example:

```PowerShell
clang++ -std=c++17 main.cpp -Xclang -ast-print -fsyntax-only > out.cpp
```
