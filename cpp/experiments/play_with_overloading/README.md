# Play with overloading

I had a struct edge and wanted to create priority queue of edges for Kruskal's algorithm. It is using operator less than to compare edges. It wasn't working and I didn't know why, so it took me a while to figure it out.

## Explanation

Files: `a.cpp`, `b.cpp`, `c.cpp`, `d.cpp` in that order explain the fix.

File `example.cpp` contains the process which helped me to see where is the problem and why it isn't working.

## Conclusion

It didn't work because I overloaded the operator as non-const member function. Read content of `example.cpp` to see more.

Oh, and no regrets by the way. I found out how to see code after preprocessor generates it, having declaration and definition in the same file alongside each other, etc.
