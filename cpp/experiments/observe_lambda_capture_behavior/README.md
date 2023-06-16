# Observe lambda capture behavior

I have been curious for a while on how does the code behavior when lambda captures by reference or value. I was sure that it uses copy and move semantics, but regardless I had to see for myself, think of a couple of examples to try out and see what happens.

## How to run

1. Compile: `.\compile.bat`
2. Run the executable. _(There should be output that says what's executable name.)_

## Observations

After this experiment I have talked to a friend, thought about it and quite a few things made sense.

Lambdas are a feature of C++. I finally started seeing what they mean lambdas are implicitly converted to function pointers and non-capturing lambda can be passed to a C function pointer. However... Once lambda captures, where does it store captured members? Lambdas are classes or structs with overloaded `operator()`.

```cpp
struct Lambda {
  void operator()() {
    // implementation...
  }
}

int main() {
  Lambda lambda{}; // Default initialization, don't omit {} - according to book
  lambda(); // call object
  return 0;
}
```

Therefore, since lambdas are C++ objects, once they capture, how would we make an object capture? Maybe through a constructor... where would it hold those values? Probably as members... pointer to a function usually means a global function or namespaced function _(I wonder if namespaced function would work...)_, anyway a global function can access global variables.

I also talked to a friend and he literally said what a StackOverflow answer did: **"There is no easy way to pass lambda that captures to a C function pointer."**

After quite some thinking and discussions it made sense, mostly thanks to me attempting to create lambda and thinking what lambdas really are and what are they differences compared to C function pointers.
