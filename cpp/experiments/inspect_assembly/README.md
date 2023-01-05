# Inspect assembly output of an object file

Not possible, object file doesn't contain assemble code. `LLDB` won't access object file because it doesn't have machine architecture.

[(Quora answer) Is the object file of a C program written in assembly language?](https://qr.ae/pryWBX)

I proceeded to inspect output from the whole executable.

## Notes

- Platform [Windows]

## Compiler Debug flags that allow LLDB to interpret executable

- [-g, --debug](https://clang.llvm.org/docs/ClangCommandLineReference.html#cmdoption-clang-g)
- [-O1](https://clang.llvm.org/docs/ClangCommandLineReference.html#cmdoption-clang-o-arg)

## Generate object file

- [-c](https://clang.llvm.org/docs/CommandGuide/clang.html#cmdoption-c)

## LLDB info

- [LLDB Tutorial](https://lldb.llvm.org/tutorial.html)

## Compile in debug mode

Two set of steps I wanted to try out:

- Use only source files
- Create object file, compile, debug afterwards

### Use only source files

Compile program:

```terminal
clang++ -g -O0 main.cpp lib.cpp -o main
```

Open debugger:

```terminal
lldb main.exe
```

Dump assembly code:

```terminal
(lldb) d
```

Set breakpoint:

```terminal
(lldb) breakpoint set --file lib.cpp --line 5
```

### Create object file, compile, debug afterwards

Create object file `lib.o`.

```terminal
clang++ -g -O0 -c lib.cpp
```

Compile program:

```terminal
clang++ -g -O0 main.cpp lib.o -o main
```

Open debugger:

```terminal
lldb main.exe
```

Dump assembly code:

```terminal
(lldb) d
```

Set breakpoint:

```terminal
(lldb) breakpoint set --file lib.cpp --line 5
```

## Steps

Once LLDB was open and breakpoint ready, run program:

```terminal
(lldb) process launch
```

[After that, I can use commands to move through the program flow.](https://lldb.llvm.org/use/tutorial.html#controlling-your-program)
