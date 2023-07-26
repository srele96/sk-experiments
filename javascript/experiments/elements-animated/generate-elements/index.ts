/**
 * Failure. I couldn't write types for a generic function within up to 4 hours
 * or however long and got bored, well next time!
 */

// Proof that other stuff that I can do fast are not easy. I couldn't create
// types for a function which feels like not much work, but turned out to be
// a whole lot of work. I spent up to 3 hours figuring out what the hell is
// going on with types and how to type stuff here... nope. I couldn't get it
// to work. I figured out if I try to write function from scratch using
// typescript I could figure out what is wrong and what types i need. It turns
// out I lack quite some skill programming with types or in strongly typed
// language. TypeScript taught me that I should do more programming in strongly
// typed language to learn to think in terms of types, especially when working
// with generic types. That was insane, i never got into so much generic logic
// and damn that was a lot... Anyway, i will save this file as a reminder for
// future me.

// Chat where I tried to figure out what to do, but gave up! F it!
// https://chat.openai.com/share/ce379cbf-e9ce-4426-a1a7-4589debca1b8

/**
 * DEFINING THE PROBLEM...
 *
 *
 *
 * an option is an object that takes in data, each and modify properties
 * from those, only data is required and must have at least one key which is an
 * array of whatever type
 * each key can be an array of whatever type user wants and each array may be
 * different type, all must be of the same length
 *
 * each is a function which receives a key which is a string and a value which
 * is an object with key value pairs
 * a value that each object gets, contains keys from data object and one key has
 * a type of value from that data object key
 * each is a function that returns an object with a key and value property, a
 * returned key may be one of the existing keys for each object
 * we have so far, initially we use as a key an index using array reduce method,
 * which is a string
 * however user is allowed to return a key that is different or something that
 * he desires to use as a key
 * the value can be the value the current key maps to, however user may modify
 * the returned value to be whatever he wants it to return
 * each function returns key value pair and the result is stored under that key
 * in the accumulated object
 *
 * modify is an object with keyA, keyB and cb properties, where keyA and keyB
 * are keys whichever user may want to use, but it should
 * be one of the available keys from the object that we accumulated so far, the
 * accumulated object is the object that we user modified from each function
 * cb is a function that receives two values, first value is mapped by keyA and
 * second value is mapped by keyB
 * cb function returns an object with two keys that map a value each of them,
 * their names are keyA and keyB
 * the returned key may already exist on the accumulated object or it may not
 * exist in which case it will be dynamically added to the accumulated object
 */

// Provide the ability to the user to specify the key and the value type
// associated to it.
//
// To constrain the value in the Data type to be an array that contains the
// specified type, you can use TypeScript's conditional types along with the
// Array utility type. Here's how you can achieve this:
type Data<T extends { [key: string]: unknown }> = {
  [K in keyof T]: T[K] extends Array<infer U> ? Array<U> : never;
};

// https://stackoverflow.com/questions/60773110/define-an-object-with-an-optional-amount-of-keys-but-at-least-one-key
type NotEmpty<T> = {} extends T ? never : T; // Exclude empty objects

type ElementTypes<D> = {
  [K in keyof D]: D[K] extends Array<infer U> ? U : never;
};

type EachReturn<V> = { key: string | number; value: V };

type Each<D, V> = (
  key: keyof ElementTypes<D>,
  value: ElementTypes<D>
) => EachReturn<V>;

interface Option<D, R> {
  data: D;
  each?: Each<D, R>;
}

// The only way I figured out to use NotEmpty is through data creator function.
function generate<T extends Data<{}>, R>(option: Option<NotEmpty<T>, R>) {}

generate<
  {
    a: number[];
    b: string[];
    c: boolean[];
  },
  {
    wtf: string;
  }
>({
  data: { a: [1], b: [], c: [] },
  each: (key, value) => {
    return { key, value: { wtf: '' } };
  },
});

type Data<T extends { [key: string]: unknown }> = {
  [K in keyof T]: T[K] extends Array<infer U> ? Array<U> : never;
};

type NotEmpty<T> = {} extends T ? never : T;

interface Option<D> {
  data: D;
}

interface K<T> {
  [key: string | number]: T;
}

interface Foo {
  a: number[];
}

function generateElements<V extends Foo, R extends K<V>, T extends Data<{}>>(
  option: Option<NotEmpty<T>>
): R {
  if (!option) {
    // error
  }

  if (!option.data) {
    // error
  }

  const keys = Object.keys(option.data);
  if (keys.length > 0) {
    let uniq = new Set<number>();
    for (const value of Object.values(option.data) as Array<unknown>[]) {
      uniq.add(value.length);
      if (uniq.size > 1) {
        // error
      }
    }
  }

  let acc: R = {
    a: [],
  };

  return acc;
}

generateElements({
  data: {
    a: [],
  },
});

type B<T = unknown> = {
  [key: string | number]: T;
};

const b: B = {};

function generateElements<T, R extends B<T>>(): R {
  let acc: R = {} as R;
  acc['a'] = {};

  return acc;
}
