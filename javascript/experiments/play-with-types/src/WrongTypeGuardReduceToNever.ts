interface A {
  foo: 'A';
  bar: string;
}

interface B {
  foo: 'B';
  baz: number;
}

const a: A | B = { foo: 'A', bar: 'hello' };
const b: B | B = { foo: 'B', baz: 1 };

// Aha... type guard is cool to assert the type of a whole object based on a
// few runtime checks that we guarantee... That we implement...

function isA_WRONG(a: A | B): a is A {
  return a.foo === 'B';
}

function isA_GOOD(a: A | B): a is A {
  return a.foo === 'A';
}

// But I thought typescript would let me be wrong here... Because I guarantee
// for the type through an implementation?
// Ah... it is not the guard issue. The issue is within the definition of `b`
// itself. It is from union type deduced that it's a type `B` and then why does
// the type guard fail? Since even though it's of type B, the type guard can
// take B and assert wrongly that it's A...
if (isA_WRONG(b)) {
  // Use the @ts-ignore because I hate the file being red in vscode
  // @ts-ignore
  console.log(b.bar);
}

if (isA_GOOD(a)) {
  a.bar;
}

function create(): A | B {
  return { foo: 'B', baz: 1 };
}

const c = create();

if (isA_GOOD(c)) {
  c.bar;
}

if (isA_WRONG(c)) {
  c.bar; // Incorrectly let me access the property of A as expected
}

function wrong(take: A | B): take is B {
  return take.foo === 'A';
}

// https://stackoverflow.com/questions/75163350/the-intersection-was-reduced-to-never-because-property-has-c

if (wrong(a)) {
  // Is there a way to check if the `a` is of type `A` or `B`?
  if ('baz' in a) {
    // Use the @ts-ignore because I hate the file being red in vscode
    // @ts-ignore
    a.baz;
  }
  if ('bar' in a) {
    // Use the @ts-ignore because I hate the file being red in vscode
    // @ts-ignore
    a.bar;
  }
  // Use the @ts-ignore because I hate the file being red in vscode
  // @ts-ignore
  a.baz;
  // Use the @ts-ignore because I hate the file being red in vscode
  // @ts-ignore
  a.bar;
  // The typescript reduced the type to `never` and we can go to hell in this
  // block...

  // Interestingly this makes sense...

  // If you're in a situation where TypeScript narrows the type of a variable
  // to never within a conditional block—due to, for example, incorrect type
  // guard usage as you've described—it means TypeScript believes it's
  // logically impossible for the code within the block to be executed. This
  // could happen when the type guard's condition contradicts the known type
  // information, leading TypeScript to conclude that no type matches the
  // condition.
}
