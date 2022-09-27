# Linear Algebra

The C++ implementation of Linear Algebra concepts.

Implementing Linear Algebra concepts helps me remember them.

## Goals

Focus on linear algebra concepts instead of computing ones.

### Example of computing problems

```txt
 ******************************************************************************
 *
 * # Problems
 *
 * A screen that shows the axis. Axis can be 1*D, 2*D, 3*D, ... N*D.
 * A screen shows vector location.
 *
 * ## Show axis
 *
 * ## Screen size
 *
 * Screen size has to be an odd number. The center is an axis.
 *
 * Vector v with values (v1=3, v2=1) requires screen size=7.
 *
 * Each diagonal has values: -3, -2, -1, 0, 1, 2, 3. In other words, it is
 * symmetric.
 *
 * ## Screen size after operation
 *
 * It is possible that the vector after operation requires a larger size.
 *
 * We can add, subtract and multiply vectors. One solution is a dynamic screen.
 * The vector values change after each operation. For the two vectors:
 * v where (v1=3, v2=1) and w where (w1=1, w2=-1) initial size of 7 is enough.
 *
 * But what after addition?
 *
 * Let vector u be the result, where (u1=4, u2=0). We require the screen size
 * of 9.
 *
 ******************************************************************************
```

### The Solution

Set up working cases to focus on concepts of linear algebra.

- Build linear algebra concepts with simplicity.
- Ignore dynamic inputs and error handling.
