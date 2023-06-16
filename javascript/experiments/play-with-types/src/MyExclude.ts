{
  interface RegularType {
    a: string;
    b: string;
  }

  // Basically SuperType satisfies constaints of RegularType and may contain
  // additional ones.
  interface SuperType extends RegularType {
    c: string;
  }

  const superTypeValue: SuperType = {
    a: '',
    b: '',
    c: '',
  };

  // My assumption is that when UnionType satisfies constraints of ExcludedMembers,
  // MyExclude would be of type `never`. That does happen when used with objects.
  // However, it works absolutely fine for union types.
  type MyExclude<UnionType, ExcludedMembers> = UnionType extends ExcludedMembers
    ? never
    : UnionType;

  // const withObjects: MyExclude<{}, {}> = {}; // Error
}
{
  // Reverse-Engineer Exclude<UnionType, ExcludedMembers>
  type First = {};
  type Second = {};

  // const a: First extends Second ? never : First = {}; // Error
}

{
  // Reverse-Engineer
  type First = { a: string };
  type Second = {};

  // const a: First extends Second ? never : First = {}; // Error
}

{
  type MyExclude<T, E> = T extends E ? never : T; // Ok, works

  type Letter = 'a' | 'b';
  type Exclude = 'a';

  // const a: MyExclude<Letter, Exclude> = 'a'; // Error
  const b: MyExclude<Letter, Exclude> = 'b';

  interface Foo {
    a: string;
  }

  interface Bar {
    a: number;
  }

  const c: MyExclude<Foo, Bar> = { a: '' };

  interface Baz {
    a: string;
  }

  // const d: MyExclude<Foo, Baz> = { a: '' }; // Error
}
