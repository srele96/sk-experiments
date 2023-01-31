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

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

type MyRecord<Type extends keyof any, Keys> = {
  [Key in Type]: Keys;
};

type Mage = 'Mage';
type Warrior = 'Warrior';
type Rogue = 'Rogue';

interface Weapon {
  name: string;
  damage: number;
}

interface Health {
  current: number;
  max: number;
}

const heroes: MyRecord<
  Mage | Warrior | Rogue,
  { weapon: Weapon; health: Health }
> = {
  Mage: {
    weapon: {
      name: 'Staff',
      damage: 10,
    },
    health: {
      current: 100,
      max: 100,
    },
  },
  Warrior: {
    weapon: {
      name: 'Sword',
      damage: 15,
    },
    health: {
      current: 150,
      max: 150,
    },
  },
  Rogue: {
    weapon: {
      name: 'Dagger',
      damage: 20,
    },
    health: {
      current: 200,
      max: 200,
    },
  },
};

// Test `keyof T`, it gives me a union of all keys of the type. So basically,
// any time I get a `keyof any` I get a union and I can iterate over it using
// `K in T`. However I can't accept unrestricted type because `keyof T` which
// is not restricted isn't what I want.
type WeaponProperties = keyof Weapon;
const weaponProperties: WeaponProperties = 'damage';
