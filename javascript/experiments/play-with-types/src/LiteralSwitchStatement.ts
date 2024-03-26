{
  enum Type {
    A,
    B,
    C,
  }

  type A = {
    type: Type.A;
    payload: string;
  };

  type B = {
    type: Type.B;
    payload: number;
  };

  type C = {
    type: Type.C;
    payload: {
      a: number;
      b: string;
    };
  };

  type D = {
    type: number;
    payload: number[];
  };

  type Foo = A | B | C | D;

  function foo(a: Foo) {
    switch (a.type) {
      case Type.A: {
        a.payload;
        break;
      }
      case Type.B: {
        a.payload;
        break;
      }
      case Type.C: {
        //   a.payload.a;
        //   a.payload.b;
        break;
      }
      default: {
        break;
      }
    }
  }

  const ob = {
    a: function a() {
      return {
        type: Type.A,
        payload: 1,
      };
    },
    b: function b() {
      return {
        type: Type.B,
        payload: 'hello',
      };
    },
    c: function c() {
      return {
        type: Type.C,
        payload: {
          a: 1,
          b: 'wtf',
        },
      };
    },
  };

  type O = keyof typeof ob;

  type T = typeof ob; // Get the type of an object
  type L = keyof T; // Get the keys of an object
  type W = [keyof T]; // Put the keys of an object in an array type
  type E = T[keyof T];

  type K = ReturnType<typeof ob[keyof typeof ob]>;

  function goo(uh: K) {
    switch (uh.type) {
      case Type.A: {
        uh.type; // cannot access uh.payload, why?
        uh.payload;
        break;
      }
      case Type.B: {
        uh.payload;
      }
      case Type.C: {
        uh.payload.a;
        uh.payload.b;
        break;
      }
    }
  }
}

{
  const ob = {
    a: function a() {
      return {
        type: 'A',
        payload: 1,
      };
    },
    b: function b() {
      return {
        type: 'B',
        payload: 'hello',
      };
    },
    c: function c() {
      return {
        type: 'C',
        payload: {
          a: 1,
          b: 'wtf',
        },
      };
    },
  };

  // Makes no sense. Why does (typeof ob) gives union type when used in
  // conjunction with array [keyof typeof ob]

  function boo(uh: ReturnType<typeof ob[keyof typeof ob]>) {
    switch (uh.type) {
      case 'A': {
        uh.payload;
        break;
      }
      case 'B': {
        uh.payload;
        break;
      }
      case 'C': {
        uh.payload.a;
        uh.payload.b;
        break;
      }
    }
  }
}

{
  const ob = {
    a: function a() {
      return {
        // to infer the type as literal, mark it as const
        type: 'A' as const,
        payload: 1,
      };
    },
    b: function b() {
      return {
        type: 'B' as const,
        payload: 'hello',
      };
    },
    c: function c() {
      return {
        type: 'C' as const,
        payload: {
          a: 1,
          b: 'wtf',
        },
      };
    },
  };

  // Makes no sense. Why does (typeof ob) gives union type when used in
  // conjunction with array [keyof typeof ob]

  function boo(uh: ReturnType<typeof ob[keyof typeof ob]>) {
    switch (uh.type) {
      case 'A': {
        uh.payload;
        break;
      }
      case 'B': {
        uh.payload;
        break;
      }
      case 'C': {
        uh.payload.a;
        uh.payload.b;
        break;
      }
    }
  }
}

{
  type U =
    | { type: 'A'; payload: { a: number; b: string } }
    | { type: 'B'; payload: { b: string } }
    | { type: 'C'; payload: { a: number } }
    | { type: 'D'; payload: number[] };

  function hoo(uh: U) {
    switch (uh.type) {
      case 'A': {
        uh.payload; // Good
        uh.payload.a;
        uh.payload.b;
        // Break statement is required, otherwise typescript gets confused,
        // because the execution falls through
        break;
      }
      case 'B': {
        uh.payload.b;
        uh.payload.a;
        break;
      }
      case 'C': {
        uh.payload.a;
        break;
      }
      case 'D': {
        uh.payload.map;
      }
    }
  }
}

{
  type Payloads = {
    A: number;
    B: string;
    C: { a: number; b: string };
  };

  function eoo(uh: {
    type: keyof Payloads;
    payload: Payloads[keyof Payloads];
  }): void {
    switch (uh.type) {
      case 'A': {
        uh.payload;
        break;
      }
      case 'B': {
        uh.payload;
        break;
      }
      case 'C': {
        uh.payload.a;
        uh.payload.b;
        break;
      }
    }
  }
}

{
  // https://stackoverflow.com/questions/52393730/typescript-string-literal-union-type-from-enum

  // treat as literals
  enum Type {
    A = 'A',
    B = 'B',
    C = 'C',
  }

  // To get a union type of literals...
  type T = `${Type}`;

  const ob = {
    a: function a() {
      return {
        type: Type.A as const,
        payload: 1,
      };
    },
    b: function b() {
      return {
        type: Type.B as const,
        payload: 'hello',
      };
    },
    c: function c() {
      return {
        type: Type.C as const,
        payload: {
          a: 1,
          b: 'wtf',
        },
      };
    },
  };

  type K = ReturnType<typeof ob[keyof typeof ob]>;

  function loo(uh: K) {
    switch (uh.type) {
      case Type.A: {
        uh.type; // cannot access uh.payload, why?
        uh.payload;
        break;
      }
      case Type.B: {
        uh.payload;
      }
      case Type.C: {
        uh.payload.a;
        uh.payload.b;
        break;
      }
    }
  }
}

{
  const ob = {
    a: function a() {
      return {
        type: 1 as const,
        payload: 1,
      };
    },
    b: function b() {
      return {
        type: 2 as const,
        payload: 'hello',
      };
    },
    c: function c() {
      return {
        type: 3 as const,
        payload: {
          a: 1,
          b: 'wtf',
        },
      };
    },
  };

  type K = ReturnType<typeof ob[keyof typeof ob]>;

  function lkad(a: K) {
    switch (a.type) {
      case 3: {
        // Works!
        a.payload.a;
        a.payload.b;
      }
    }
  }
}

{
  const ob = {
    a: function a() {
      return {
        type: 1 as const,
        payload: 1,
      };
    },
    b: function b() {
      return {
        type: 2 as const,
        payload: 'hello',
      };
    },
    c: function c() {
      return {
        type: 3 as const,
        payload: {
          a: 1,
          b: 'wtf',
        },
      };
    },
  };

  interface Bar {
    a: number[];
    b: string[];
    c: { a: number; b: string };
  }
  interface Baz {
    a: { b: number };
    b: typeof ob;
    c: string;
  }

  type K = ReturnType<typeof ob[keyof typeof ob]>;

  type L = Bar[keyof Baz];
  type O = Baz[keyof Baz];
  type P = Bar[keyof Bar];
}

{
  interface A {
    foo: 'A';
    bar: string;
  }

  interface B {
    foo: 'B';
    baz: number;
  }

  const a: A = { foo: 'A', bar: 'hello' };
  const b: B = { foo: 'B', baz: 1 };

  // Aha... type guard is cool to assert the type of a whole object based on
  // a few runtime checks that we guarantee... That we implement...

  function isA_WRONG(a: A | B): a is A {
    return a.foo === 'B';
  }

  function isA_GOOD(a: A | B): a is A {
    return a.foo === 'A';
  }

  // But I thought typescript would let me be wrong here... Because I guarantee
  // for the type through an implementation?
  if (isA_WRONG(b)) {
    b.bar;
  }

  if (isA_GOOD(a)) {
    a.bar;
  }

  // I think I understand... even the a is of a union type, both guarantee foo
  // access, but the second property is not guaranteed... Why?

  // I see... makes sense... a function that takes a union is useful to narrow
  // down the type based on a common property...
  function accept(a: A | B) {
    a.foo; // Ok, why?

    if (typeof a.foo === 'string') {
      // There is no guarantee about other properties on `a`
      a.bar; // Not OK
    }

    if (a.foo === 'A') {
      a.bar; // Ok
    }

    if (a.foo === 'B') {
      a.baz; // Ok
    }

    switch (a.foo) {
      case 'A': {
        a.bar; // Ok
        break; // Fixes the issue of control flow falling through
      }
      case 'B': {
        a.baz; // Not OK because the control flow falls through
        break;
      }
    }
  }

  // a function that takes different types and can not narrow down based on a
  // common property... actually... let me think...
  function acceptTwo(a: A | B) {}
}
