# How to use LLDB

Using LLDB is exhilarating! I freakin love it! I am going to write down how I used it to debug a C++ program that I wrote. I first tried to debug it using `std::cout` but it was... ew... I was hesitant on using LLDB, but it turned out to be one of the best decisions! I was hesitant because I didn't know the syntax, how to run it, etc... However... It was so freakin good! Let's goooooo!!!!!

## Steps

### Compile the program in debug mode

First, we have to compile the program. Compiler performs optimizations, so we have to compile it using flags that will preserve as much of it as possible. These flags are modifiable, however, I used these:

According to ChatGPT, recommended `-g` level is `2`, however I used 3 because it's maximum. Higher level means larger executable, the program was small, so it was ok!

Do not perform any kind of optimizations on the code, that's what `-O0` does.

- [`-g3`](https://clang.llvm.org/docs/ClangCommandLineReference.html#debug-level)
- [-O0](https://clang.llvm.org/docs/ClangCommandLineReference.html#optimization-level)

My program was in one file `test.cpp` and I compiled it to `test.exe`.

```powershell
clang++ -g3 -O0 test.cpp -o test
```

### Alright, let's debug it!

Hold on! We have to run the debugger... Well, no worries!

```powershell
lldb
```

That command runs the debugger. However, we have to load the executable!

We should see in the powershell something like following. That means we are inside the debugger process.

```powershell
(lldb)
```

Let's see what are the commands?

```powershell
(lldb) help
```

And we get a bunch of commands this time! Let's load the executable!

```powershell
(lldb) target create test.exe
```

Now, it should say that executable is loaded. Let's run it!

```powershell
(lldb) process launch
```

That will run the process, however it will just execute and exit because we didn't tell it where to stop. Let's set a breakpoint!

I already used debugger so I know this, but anyway... I set this variable inside a function where I wanted to see what are the values of my variables.

```powershell
(lldb) breakpoint set --file test.cpp --line 5
```

That will set a breakpoint on line 5 of `test.cpp`. Let's run it again!

```powershell
(lldb) process launch
```

Now, the debugger should stop. We can see the variables in the current scope _(i hope i got that right...)_ using `frame variable` command.

```powershell
(lldb) frame variable
```

etc...

Stepping in!

```powershell
(lldb) thread step-in
```

Stepping over!

```powershell
(lldb) thread step-over
```

Stepping out!

```powershell
(lldb) thread step-out
```

_**I omitted some steps below, for example compilation, loading executable, etc... I just created example program to make it more obvious what are the steps to print content of a variable.**_

Print the content of specific variable on this example file:

```cpp
int main() {
  int my_var = 5;

  return 0;
}
```

Set breakpoint to line below my var so it is initialized:

```powershell
(lldb) breakpoint set --file test.cpp --line 3
```

Run the program:

```powershell
(lldb) process launch
```

Print the content of `my_var`:

```powershell
(lldb) print my_var
```

## Story

I wrote a C++ program of roughly 230 lines and I had a bug... I tried to debug it using `std::cout`, but boy that sucked... I didn't use `C++` debuggers before, I did... but only to play around with a couple of commands! Hence... I wasn't sure whether I can do it! However, thanks to my super-duper previous documentation I could get it running fast!

This command compiled the code so I can use debugger on it!

```powershell
clang++ -g3 -O0 -std=c++17 test.cpp -o test
```

And after that I could simply fire up the debugger:

```powershell
lldb
```

Then from within debugger process, I could load the executable and run it!

Load executable:

```powershell
(lldb) target create ./build/test.exe
```

Launch debugging process:

```powershell
(lldb) process launch
```

There was a bit more... but that's the gist of it!

However, I noticed what the issue was really fast when using debugger. I was accessing the variable using wrong value. I was surprised that the program didn't crash since it could have easily chosen the variable that's out of bounds... Actually it couldn't, because I prevented it by removing the pointers that point to invalid element _that are out of vector's bounds_.

Anyway... That was lots of fun and oh boy am I glad I did that!
