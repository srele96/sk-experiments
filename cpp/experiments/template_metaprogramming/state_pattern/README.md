# State pattern

A state pattern implementation using C++.

## Table of Content

- [State pattern](#state-pattern)
  - [Table of Content](#table-of-content)
  - [References](#references)
  - [Compile](#compile)

## References

- [Game Programming Patterns](http://gameprogrammingpatterns.com/state.html)
- [Wikipedia Design Patterns](https://en.wikipedia.org/wiki/Design_Patterns)
- [State Pattern](https://en.wikipedia.org/wiki/State_pattern)
- [Stackoverflow forward declaration](https://stackoverflow.com/questions/15076026/c-forward-declaration-and-incomplete-type-is-not-allowed-error)
  - _(I had to split files to header and implementation because concrete state implementations could not instantiate each other.)_

## Compile

```powershell
g++ -std=c++17 main.cpp jump.cpp run.cpp context.cpp idle.cpp -o main.exe; ./main
```
