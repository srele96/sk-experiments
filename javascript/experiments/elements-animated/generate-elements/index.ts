// // /**
// //  * Failure. I couldn't write types for a generic function within up to 4 hours
// //  * or however long and got bored, well next time!
// //  */

// // // Proof that other stuff that I can do fast are not easy. I couldn't create
// // // types for a function which feels like not much work, but turned out to be
// // // a whole lot of work. I spent up to 3 hours figuring out what the hell is
// // // going on with types and how to type stuff here... nope. I couldn't get it
// // // to work. I figured out if I try to write function from scratch using
// // // typescript I could figure out what is wrong and what types i need. It turns
// // // out I lack quite some skill programming with types or in strongly typed
// // // language. TypeScript taught me that I should do more programming in strongly
// // // typed language to learn to think in terms of types, especially when working
// // // with generic types. That was insane, i never got into so much generic logic
// // // and damn that was a lot... Anyway, i will save this file as a reminder for
// // // future me.

// // // Chat where I tried to figure out what to do, but gave up! F it!
// // // https://chat.openai.com/share/ce379cbf-e9ce-4426-a1a7-4589debca1b8

// // /**
// //  * DEFINING THE PROBLEM...
// //  *
// //  *
// //  *
// //  * an option is an object that takes in data, each and modify properties
// //  * from those, only data is required and must have at least one key which is an
// //  * array of whatever type
// //  * each key can be an array of whatever type user wants and each array may be
// //  * different type, all must be of the same length
// //  *
// //  * each is a function which receives a key which is a string and a value which
// //  * is an object with key value pairs
// //  * a value that each object gets, contains keys from data object and one key has
// //  * a type of value from that data object key
// //  * each is a function that returns an object with a key and value property, a
// //  * returned key may be one of the existing keys for each object
// //  * we have so far, initially we use as a key an index using array reduce method,
// //  * which is a string
// //  * however user is allowed to return a key that is different or something that
// //  * he desires to use as a key
// //  * the value can be the value the current key maps to, however user may modify
// //  * the returned value to be whatever he wants it to return
// //  * each function returns key value pair and the result is stored under that key
// //  * in the accumulated object
// //  *
// //  * modify is an object with keyA, keyB and cb properties, where keyA and keyB
// //  * are keys whichever user may want to use, but it should
// //  * be one of the available keys from the object that we accumulated so far, the
// //  * accumulated object is the object that we user modified from each function
// //  * cb is a function that receives two values, first value is mapped by keyA and
// //  * second value is mapped by keyB
// //  * cb function returns an object with two keys that map a value each of them,
// //  * their names are keyA and keyB
// //  * the returned key may already exist on the accumulated object or it may not
// //  * exist in which case it will be dynamically added to the accumulated object
// //  */

// // // Provide the ability to the user to specify the key and the value type
// // // associated to it.
// // //
// // // To constrain the value in the Data type to be an array that contains the
// // // specified type, you can use TypeScript's conditional types along with the
// // // Array utility type. Here's how you can achieve this:
// // type Data<T extends { [key: string]: unknown }> = {
// //   [K in keyof T]: T[K] extends Array<infer U> ? Array<U> : never;
// // };

// // // https://stackoverflow.com/questions/60773110/define-an-object-with-an-optional-amount-of-keys-but-at-least-one-key
// // type NotEmpty<T> = {} extends T ? never : T; // Exclude empty objects

// // type ElementTypes<D> = {
// //   [K in keyof D]: D[K] extends Array<infer U> ? U : never;
// // };

// // type EachReturn<V> = { key: string | number; value: V };

// // type Each<D, V> = (
// //   key: keyof ElementTypes<D>,
// //   value: ElementTypes<D>
// // ) => EachReturn<V>;

// // interface Option<D, R> {
// //   data: D;
// //   each?: Each<D, R>;
// // }

// // // The only way I figured out to use NotEmpty is through data creator function.
// // function generate<T extends Data<{}>, R>(option: Option<NotEmpty<T>, R>) {}

// // generate<
// //   {
// //     a: number[];
// //     b: string[];
// //     c: boolean[];
// //   },
// //   {
// //     wtf: string;
// //   }
// // >({
// //   data: { a: [1], b: [], c: [] },
// //   each: (key, value) => {
// //     return { key, value: { wtf: '' } };
// //   },
// // });

// // type Data<T extends { [key: string]: unknown }> = {
// //   [K in keyof T]: T[K] extends Array<infer U> ? Array<U> : never;
// // };

// // type NotEmpty<T> = {} extends T ? never : T;

// // interface Option<D> {
// //   data: D;
// // }

// // interface K<T> {
// //   [key: string | number]: T;
// // }

// // interface Foo {
// //   a: number[];
// // }

// // function generateElements<V extends Foo, R extends K<V>, T extends Data<{}>>(
// //   option: Option<NotEmpty<T>>
// // ): R {
// //   if (!option) {
// //     // error
// //   }

// //   if (!option.data) {
// //     // error
// //   }

// //   const keys = Object.keys(option.data);
// //   if (keys.length > 0) {
// //     let uniq = new Set<number>();
// //     for (const value of Object.values(option.data) as Array<unknown>[]) {
// //       uniq.add(value.length);
// //       if (uniq.size > 1) {
// //         // error
// //       }
// //     }
// //   }

// //   let acc: R = {
// //     a: [],
// //   };

// //   return acc;
// // }

// // generateElements({
// //   data: {
// //     a: [],
// //   },
// // });

// // type B<T = unknown> = {
// //   [key: string | number]: T;
// // };

// // const b: B = {};

// // function generateElements<T, R extends B<T>>(): R {
// //   let acc: R = {} as R;
// //   acc['a'] = {};

// //   return acc;
// // }

// /**
//  * Fundamentally I have to apply divide and conquer approach to the problem.
//  * I have to continuously try to solve the problem, learn about problems I am
//  * not aware of. Write them down, try to solve them. If more problems arise,
//  * rinse and repeat. I thought that I understood the problem, once I started
//  * to solve it I understood that I don't understand it. Then came back the next
//  * day and thought I understood the problem, however realized that I don't
//  * understand it again. I have to keep trying to solve it, learn about the new
//  * problems and think if I understand it all, then try to solve it again.
//  * Repeating the process until I solve it. Then I thoroughly test it and find
//  * out that I did not understand something and it's not working as intended,
//  * then go back to see what's up and understand the problem, then solve it
//  * again. The process repeats until the user finds an issue or I find an issue
//  * and it never ends!
//  *
//  * Tried again, didn't work out. I now understand that the function returns a
//  * different type based on the options that we pass to it. I am not used to
//  * thinking in terms of types.
//  *
//  * JavaScript is dynamic language and doesn't teach you to think in terms of
//  * types. The current implementation is generic, however I never before had to
//  * think in terms of generic programming which is challenging.
//  *
//  * I am obviously lacking some elementary typescript and generic programming
//  * skills.
//  *
//  * I will have to learn more about it.
//  *
//  * However after playing around for an hour and a half I learned more about
//  * the problems of the current function which I did not know existed.
//  *
//  * I would need to play with following concepts to understand them before I
//  * can comfortably type this function.
//  *
//  * - Function changes type based on the options it receives.
//  * - User may declare a type for one of the function options.
//  * - We are mapping values of the provided user option and fundamentally
//  *    changing it's shape, which means we are redefining it's type.
//  * - We are placing constraints on the user provided option type:
//  *   - At lest one key must be provided.
//  *   - All keys must be arrays.
//  *   - Each array may contain it's own type.
//  */

// interface Option<V> {
//   data: {
//     [key: string | number]: never[];
//   };
//   each?: (key: string, value: unknown) => { key: string; value: V };
// }

// interface KeyValue<V> {
//   [key: string | number]: V;
// }

// interface Accumulator {
//   [key: string]: {
//     [key: string]: unknown;
//   };
// }

// const fn = <V>(option: Option<V>): KeyValue<V> | Accumulator => {
//   if (!option) {
//     // error
//   }

//   if (!option.data) {
//     // error
//   }

//   const keys = Object.keys(option.data);
//   if (keys.length > 0) {
//     let lengths = new Set<number>();
//     for (const value of Object.values(option.data)) {
//       if (!Array.isArray(value)) {
//         // Error
//       }
//       lengths.add(value.length);
//       if (lengths.size > 1) {
//         // Error
//       }
//     }
//   } else {
//     // Error
//   }

//   const temporaryAccumulator: Accumulator = {};

//   for (const key in option.data) {
//     const value = option.data[key];
//     for (let i = 0; i < value.length; ++i) {
//       if (!temporaryAccumulator[i]) {
//         temporaryAccumulator[i] = {};
//       }

//       temporaryAccumulator[i][key] = value[i];
//     }
//   }

//   let accumulator: KeyValue<V>;

//   const fnEach = option.each;
//   if (fnEach) {
//     accumulator = Object.entries(temporaryAccumulator).reduce(
//       (accumulated, [key, value]) => {
//         const result = fnEach(key, value);

//         if (!result) {
//           // Error
//         }

//         if (!result.key) {
//           // Error
//         }

//         accumulated[result.key] = result.value;

//         return accumulated;
//       },
//       {}
//     );
//   }

//   return accumulator;
// };

// // OK - I expected only return type to be like follows
// fn<{
//   [key: string]: {
//     a: string;
//     b: string;
//     c: number;
//   };
// }>({
//   data: {
//     a: [1, ''],
//   },
// });

// // NOT OK - Not expected
// fn<{
//   a: number;
//   c: number;
// }>({
//   data: {},
// });

/**
 * Data is a user provided type where a key maps to an object, examples:
 *
 * User should be able to call function without provided type
 *
 * fn({
 *   data: {
 *     a: [1, 2],
 *     b: ['a', 'b']
 *   }
 * })
 *
 * fn({}) // error
 *
 * fn({
 *   data: {} error
 * })
 *
 * fn({
 *   data: {
 *     a: [1, 2], // At least one key, OK
 *   }
 * })
 *
 * User should be able to provide a type for the data
 *
 * fn<{
 *   a: number[];
 *   b: string[];
 * }>({
 *   a: [1, 2],
 *   b: ['a', 'b']
 * })
 *
 * fn<{}>({}) // error, at least one key
 *
 * fn<{
 *   a: number; // error, must be an array
 * }>({
 *   a: 1
 * })
 *
 * fn<{
 *   a: number[];
 *   b: boolean; // error, must be an array
 * }>({})
 *
 *
 * fm<{
 *   a: boolean[]; // OK
 *   b: string[]; // OK
 * }>({
 *   data: {
 *     a: [], // OK
 *     b: [] // OK
 *   }
 * })
 */

// type KeyCollection = { [key: string | number]: unknown };

// type Data<T extends KeyCollection> = {
//   [K in keyof T]: T[K] extends Array<infer U> ? Array<U> : never;
// };

// type DataNonArray<T extends KeyCollection> = {
//   [K in keyof T]: T[K] extends Array<infer U> ? U : never;
// };

// interface KeyedData<T extends KeyCollection> {
//   [key: string]: DataNonArray<T>;
// }

// type EachReturn<V> = { key: string | number; value: V };

// type Each<D extends KeyCollection, V = DataNonArray<D>> = (
//   key: keyof D,
//   value: DataNonArray<D>
// ) => EachReturn<V>;

// interface Ret<D extends KeyCollection> {
//   [key: string]: DataNonArray<D>;
// }

// interface Option<D extends KeyCollection, V> {
//   data: Data<D>;
//   each?: Each<D, V>;
// }

// function fn<D extends KeyCollection, V = DataNonArray<D>>(
//   option: Option<D, V>
// ): Ret<D> {
//   let acc: Ret<D> = {};

//   for (const key in option.data) {
//     const value = option.data[key];
//     for (let i = 0; i < value.length; ++i) {
//       if (!acc[i]) {
//         acc[i] = {} as DataNonArray<D>;
//       }

//       acc[i][key] = value[i] as DataNonArray<D>[keyof D];
//     }
//   }

//   const each = option.each;
//   if (each) {
//     acc = Object.entries(acc).reduce((accumulated, [key, value]) => {
//       const result = each(key, value as DataNonArray<D>);

//       if (!result) {
//         // Error
//       }

//       if (!result.key) {
//         // Error
//       }

//       accumulated[result.key] = result.value;

//       return accumulated;
//     }, {});
//   }

//   return acc;
// }

// {
//   type Foo<T extends KeyCollection> = {
//     [K in keyof T]: T[K] extends Array<infer U> ? Array<U> : never;
//   };

//   const data: Foo<{
//     a: string;
//   }> = {
//     a: '',
//   };

//   data.a = '';
// }

// {
//   const data: Data<{
//     a: number[];
//   }> = {
//     a: [],
//   };
// }

// {
//   const result = fn<{
//     a: number[];
//   }>({
//     data: {
//       a: [1, 2],
//     },
//   });

//   result[0].a;
// }

// {
//   const result = fn<number>({
//     data: {},
//   });
// }

// {
//   fn<{}>({
//     data: {},
//   });
// }

// {
//   fn<{
//     a: number[];
//   }>({
//     data: {
//       a: [],
//     },
//     each: (key, value) => {
//       return { key, value };
//     },
//   });
// }

// {
//   fn({
//     data: {},
//     each: (key, value) => {
//       return { key, value };
//     },
//   });
// }

// {
//   const result = fn<
//     {
//       a: number[];
//     },
//     {
//       a: number;
//     }
//   >({
//     data: {
//       a: [],
//     },
//     each: (key, value) => {
//       return {
//         key,
//         value: {
//           a: 1,
//           b: '',
//           c: [3],
//           d: [],
//         },
//       };
//     },
//   });

//   result[0].a;
//   result[0].b;
//   result[0].c;

//   let a = result['0'].a;
//   const b = result['0'].b;
//   const c = result['0'].c;
//   const d = result['0'].d;
// }

interface KeyedCollection {
  [key: string | number]: unknown;
}

type Data<T extends KeyedCollection> = {
  [K in keyof T]: T[K] extends Array<infer U> ? Array<U> : never;
};

type DefaultResult<T extends KeyedCollection> = {
  [K in keyof T]: T[K] extends Array<infer U> ? U : never;
};

interface EachReturn<T> {
  key: string | number;
  value: T;
}

type EachCallback<R> = (key: string, value: R) => EachReturn<R>;

type ModifyReturn<R> = { keyA: R; keyB: R };

type ModifyCallback<R> = (valueA: R, valueB: R) => ModifyReturn<R>;

interface Option<T extends KeyedCollection, R> {
  data: Data<T>;
  each?: EachCallback<R>;
  modify?: {
    keyA: string;
    keyB: string;
    cb: ModifyCallback<R>;
  };
}

interface KeyValue<T extends KeyedCollection, R = unknown> {
  // if R is provided then use it, otherwise use default result
  [key: string]: R extends unknown ? DefaultResult<T> : R;
}

function fn<T extends KeyedCollection, R = unknown>(
  option: Option<T, R>
): KeyValue<T, R> {
  return {};
}

{
  const result = fn<
    {
      a: number[];
    },
    {
      a: number;
    }
  >({
    data: {
      a: [1, 2],
    },
  });

  result['0'].a;
  result['1'].b;
}

{
  const result = fn<{
    a: number[];
    b: string[];
  }>({
    data: {
      a: [],
      b: [],
    },
  });

  result['0'].a;
  result['0'].b;

  type R = typeof result['0'];
}
