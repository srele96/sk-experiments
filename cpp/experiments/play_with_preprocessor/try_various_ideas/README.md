# Play with preprocessor

Play with preprocessor using `clang++ -E main.cpp -o main.i` command.

## How to run

On windows to create the preprocessed file run:

```cmd
create
```

Or:

```cmd
create.bat
```

## Goals

- See the behavior of various macros
- See the behavior of includes
- See various other behaviors of preprocessed code
- Save this experiment for future references

## Command

Reference on `-E` flag in [clang command line reference](https://clang.llvm.org/docs/ClangCommandLineReference.html#cmdoption-clang-e).

Preprocess using clang++.

```cmd
clang++ -E main.cpp -o main.i
```

Preprocess using g++.

```cmd
g++ -E main.cpp -o main.i
```

## Observations

- Errors don't matter.
- Preprocessor doesn't care about the syntax of the code.
- Preprocessor replaces macros with their values.
- After preprocessor runs, everything ends up in one file. So, if there are multiple files, they are all included in the same file. Anything outside of namespace is global.
- It apepars macro can be defined anywhere.
- It appears macro can be used anywhere.
- I can choose do I want to run preprocessor, compiler, assembler, linker or any of them.
- I should read whole clang or g++ manual to get insight into what's possible and what isn't.
- Reading documentation to assemble solution is much more efficient than following tutorial. A tutorial yields fixed set of steps to create solution, documentation yields individual tools and power to assemble solution.

## Conditional includes

I spent two years working with JavaScript tooling and there is possibility of conditional file inclusion. C++ supports it apparently, but I guess usage practice is the same, use where makes sense. In the past two years, I never had situation where I had to do conditional file inclusion. However it's good to know that it's possible and that I have familiar experience with it.

## Conditional definitions

Apparently this is also doable in both languages.

## Definition and declaration

1. Declaration is in header file.
2. Definition is in source file.
3. Include header file in source file. Preprocessor replaces header file with declaration. Definition is missing.
4. Pass source files to compiler.
5. Why am i passing source files to the compiler?
