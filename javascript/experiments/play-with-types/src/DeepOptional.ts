/**
 * Make each key optional.
 * If type of the key is object, repeat : otherwise assign it its own type.
 */
type DeepOptional<T> = {
  [K in keyof T]?: T[K] extends object ? DeepOptional<T[K]> : T[K];
};

/**
 * Make each key optional.
 */
type FirstLevelOptional<T> = {
  [K in keyof T]?: T[K];
};

interface Keys {
  a: number;
  b: string;
  c: {
    d: number;
    e: {
      f: number;
    };
  };
}

// Test
const firstLevelOptional: FirstLevelOptional<Keys> = {
  a: 1,
  b: '2',
  // c: {}, // Error
};

// Test
const deepOptional: DeepOptional<Keys> = {
  a: 1,
  b: '2',
  c: {}, // Ok
};
