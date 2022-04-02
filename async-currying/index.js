// print input to check execution order of inner functions
async function a(a) {
  console.log({ a });
  return async function b(b) {
    console.log({ a, b });
    return async function c(c) {
      console.log({ a, b, c });
    };
  };
}

/**
 * Asynchronous JavaScript execution order
 */
(async function () {
  // check if execution below is blocked
  await (
    await (
      await a(1)
    )(2)
  )(3);

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
      // return a promise to be resolved by next one
      // no return should throw an error

      // return used to be explicit that value must be returned
      // not immediately visible in arrow functions
      return b(5);
    })
    .then((c) => {
      return c(6);
    });
})();

(async function () {
  // check how does this execute paired with await above
  await (
    await (
      await a(7)
    )(8)
  )(9);

  a(10)
    .then((b) => {
      return b(11);
    })
    .then((c) => {
      return c(12);
    });

  a(13)
    .then((b) => b(14))
    .then((c) => c(15));
})();

let start = new Date().getSeconds();
let now = null;
// block call stack for 1 second
while (true) {
  now = new Date().getSeconds();
  if (now > start + 1) break;
}
