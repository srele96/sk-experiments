# Function parameter reference vs value

What is the usage difference? What about mutations, do they persist?

## Specs

Some functions use:

```c++
template <class C>
void f(C& c) { /_ ...implementation _/}
```

The others use:

```c++
template <class C>
void f(C c) { /_ ...implementation _/ }
```

I think that both work, what is the difference? The later takes C, but former takes reference to C.

Let's try to figure it out.

- Implement the two functions, one takes C and the other reference to C.
- Pass them an object.
- Note the use differences. Can the function use them the same way?
- What if we print, mutate, then print parameter?
- Implement two examples, using base type like char and an object.
- Does the mutation on object property persist outside of function?
- Does the mutation on character persist outside of function?
