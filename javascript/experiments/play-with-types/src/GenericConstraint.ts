{
  const data = { name: 'John' };

  type DataWithOptionalProperties = {
    [Key in keyof typeof data]?: typeof data[Key];
  };

  const data2: DataWithOptionalProperties = {};
}

{
  const data = { name: 'John' };

  /**
   * Assigns a default type to generic type parameter `T`, but provided type
   * can be anything.
   */
  type DataWithOptionalProperties<T = typeof data> = {
    [Key in keyof T]?: T[Key];
  };

  const data2: DataWithOptionalProperties = {};

  // A type parameter can be anything
  const data3: DataWithOptionalProperties<{ lastName: string }> = {
    lastName: 'Doe',
  };
}

{
  const data = { name: 'John' };

  /**
   * Doesn't provide a default type to generic type parameter `T` and requires
   * type `T` to contain field `name` of type `string.
   */
  type DataWithOptionalProperties<T extends typeof data> = {
    [Key in keyof T]?: T[Key];
  };

  const data3: DataWithOptionalProperties<{ name: string; lastName: string }> =
    {
      lastName: 'Doe',
    };

  // A type parameter must contain at least field `name` of type `string`
  // const data4: DataWithOptionalProperties<{ lastName: string }> = {}; // Error
}

{
  const data = { name: 'John' };

  /**
   * Combines the two. Provided type must contain field `name` of type `string`
   * and has a default type.
   */
  type DataWithOptionalProperties<T extends typeof data = typeof data> = {
    [Key in keyof T]?: T[Key];
  };

  const data2: DataWithOptionalProperties = {};

  // Provided type is missing a field `name` of type `string`.
  // const data3: DataWithOptionalProperties<{ lastName: string }> = {}; // Error

  const data4: DataWithOptionalProperties<{ name: string; lastName: string }> =
    {};
}
