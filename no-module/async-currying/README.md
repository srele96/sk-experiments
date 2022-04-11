# Currying, Async Await, Promises and JavaScript execution order

Covered cases:

- Currying, regular and asynchronous functions.
- Promises execution order.
- Blocking JavaScript execution.
- How does async, await syntax block execution?

## Note

Examples below assume readers familiarity with following topics:

- Asynchronous JavaScript
- Promises
- Async and Await
- Currying

Printing output like this may ease up debugging, which is what I used:

```js
const a = 5;
console.log({ a });
```

## Currying of regular and asynchronous functions

Curried functions are functions that return functions, which means result may be invoked.

### Currying of regular functions

```js
function a(a) {
  console.log({ a });
  return function b(b) {
    console.log({ a, b });
    return function c(c) {
      console.log({ a, b, c });
    };
  };
}
```

Regular curried functions are called like following:

```js
a(1)(2)(3);
```

Another way to call curried functions:

```js
var b = a(1);
var c = b(2);
c(3);
```

### Currying of asynchronous functions

```js
async function a(a) {
  console.log({ a });
  return async function b(b) {
    console.log({ a, b });
    return async function c(c) {
      console.log({ a, b, c });
    };
  };
}
```

How do I call this?

Asynchrnous functions are promises, one way to call promise is:

```js
a(1).then(/*...*/).catch(/*...*/);
```

_But I want to call curried asynchronous functions like regular ones._

What about await?

```js
(async function () {
  console.log(await a(1));
})();
```

This does the job, but it prints two things:

- Value of parameter
- Returned function name

This made me realize, if `await a(1)` returns a function, i can await again.

```js
(async function () {
  console.log(await (await a(1))(2));
})();
```

And again:

```js
(async function () {
  console.log(await (await (await a(1))(2))(3));
})();
```

## Promises execution order

JavaScript goes through the code, puts promises and async functions on microtask stack, finishes with regular blocking JavaScript code, then executes promises.

Promises are placed on microtask stack, any promise called inside is placed after previous one calls it.

Check the following code:

```js
async function a(a) {
  console.log({ a });
  return async function b(b) {
    console.log({ a, b });
    return async function c(c) {
      console.log({ a, b, c });
    };
  };
}

(async function () {
  await (
    await (
      await a(1)
    )(2)
  )(3);

  a(1)
    .then((b) => b(2))
    .then((c) => c(3));

  a(4)
    .then((b) => {
      return b(5);
    })
    .then((c) => {
      return c(6);
    });
})();
```

### Order of execution

_These are terms I came up with_

1. Enqueue
2. Execute & Enqueue
3. Execute & Enqueue
4. ...

After execution, every called promise _on the same level_ is enqueued.

The order of execution:

1. enqueue `IIFE` async function
2. enqueue `await a(1)`
3. execute `await a(1)`
4. enqueue `await b(2)`
5. execute `await b(2)`
6. enqueue `await c(3)`
7. execute `await c(3)`
8. enqueue `a(1)`
9. enqueue `a(4)`
10. execute `a(1)`
11. enqueue `b(2)`
12. execute `a(4)`
13. enqueue `b(5)`
14. execute `b(2)`
15. enqueue `c(3)`
16. execute `b(5)`
17. ...

### Disruptions in promise execution

- await blocks code execution below (inside async function)
- chained promises don't block execution
- unknown execution time may cause promise to execute last

## Promises execution order with blocked stack

Regular JavaScript code fills function call stack, next set of enqueued promises is executed when current call stack is empty.

The following code will block execution for 1 second:

```js
let start = new Date().getSeconds();
let now = null;
// block javascript execution for 1 second
while (true) {
  now = new Date().getSeconds();
  if (now > start + 1) break;
}
```

However, if we run the file, there are two function calls before loop and they will be executed.

_Every time call stack is empty, enqueued tasks will execute._

_I am not sure if I got this correctly._

## How does async, await syntax block execution?

Inside `IIFE`, first calls use `await` syntax. These will block execution below, code below won't be picked up and enqueued.

This is **probably** why `await` cannot be used outside of `async` functions.
