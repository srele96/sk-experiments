# Return Semantics

I tried various behavior out of curiosity about how C++ handles function return values. For example, does it copy, move, or do I need to make a proper decision based on my use case?

## How to run

Windows:

```txt
run.bat <filename>
```

Use only filename without extension. For example for `template.cpp` run:

```cmd
run.bat template
```

Or another file `move_semantics.cpp`:

```cmd
run.bat move_semantics
```

## Motivation

I thought about how C++ handles return function calls of containers. Since there are construction, destruction, copy, and move semantics, it must use them for containers' return statements.

## Conclusion

The most suitable answer is that I need to handle them based on my use case. It feels like too much about how many variants there are. For example, sometimes it calls a constructor when the return value is `return Foo{}`, but when I create, modify and return that value, it moves it. If I define a constructor, I must define all other container semantics. Since a compiler will call copy constructor, destructor, and others, they should handle non-trivial data. Therefore I guess that if I want to write a good C++ program, I would need to set up a linter and strict flags to warn me about misusing features of C++ and shooting myself in the leg.
