/**
 * Restrict Type to be a valid union of keys. That is required because I have
 * to iterate over union of keys to give it a type of `Keys`. To be sure that
 * I can iterate over it, I must restrict it before I receive it. Alternative
 * would be to do: `type MyRecord<Type extends string | number | symbol, Keys>`.
 */
type MyRecord<Type extends keyof any, Keys> = {
  [Key in Type]: Keys;
};

type Mage = 'Mage';
type Warrior = 'Warrior';
type Rogue = 'Rogue';

type Hero = Mage | Warrior | Rogue;

interface Weapon {
  name: string;
  damage: number;
}

interface Health {
  current: number;
  max: number;
}

interface Properties {
  weapon: Weapon;
  health: Health;
}

const hero: MyRecord<Hero, Properties> = {
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

/**
 * Test `keyof T`, it gives me a union of all keys of the type. So basically,
 * any time I get a `keyof any` I get a union and I can iterate over it using
 * `K in T`. However I can't accept unrestricted type because `keyof T` which
 * is not restricted isn't what I want.
 */
type WeaponProperties = keyof Weapon;
const weaponProperties: WeaponProperties = 'damage';
