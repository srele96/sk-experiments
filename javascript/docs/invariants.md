# Invariants

In computer science, we try to assess whether our solutions are correct or not. To do it, we always make assumptions such as:

- If the code does what I want it to, it works.

This assumption is the basis, among others.

When I first learned about invariants, I wasn't sure what are they and how are they used. After having that on my mind for a while, I noticed a pattern. They assume and assess. The same what I do when I code. That's when it clicked. There are many types of invariants, loop, class, etc.

Invariants for linear search algorithm could be:

1. It goes through all elements.
2. It saves the index of the element that equals searched value.
3. A saved index is always the correct value, found or not found.
4. It returns the correct value.

Three properties of the loop invariant:

1. It is true before the loop stats.
2. If it is true before the loop, it is also true after loop iteration.
3. When the loop terminates, they provide usefull information about the result.

```js
function find(arr, v) {
  let n = null;
  let i = 0;

  for (i; i < arr.length; i++) {
    if (arr[i] === v) n = i;
  }

  return n;
}
```

If the following invariants are true, we can assess that algorithm performs calculation correctly.

- If the function call `find(arr, 3)` returns `2`, the algorithm correctly found value.
- If the function call `find(arr, 6)` returns `null`, the algorithm correctly did not find the value.

Determine statements that assess the correctness. These statements are invariants.

There are many types of invariants: class, loop, etc.
