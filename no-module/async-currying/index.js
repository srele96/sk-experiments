// print arguments for each function respectively
// to see when each function is called
async function a(a) {
  console.log({ a });
  return async function b(b) {
    console.log({ a, b });
    return async function c(c) {
      console.log({ a, b, c });
    };
  };
}

// The two following IIFE are used to check
// in which order promises are resolved

(async function () {
  // Used to check if execution below is blocked
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
      // use explicit return statement so it is immediately
      // clear for reader that result must be returned
      return b(5);
    })
    .then((c) => {
      return c(6);
    });
})();

(async function () {
  // check when does this get executed compared to
  // first invocation in previous IIFE
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
// block javascript execution for 1 second
while (true) {
  now = new Date().getSeconds();
  if (now > start + 1) break;
}
