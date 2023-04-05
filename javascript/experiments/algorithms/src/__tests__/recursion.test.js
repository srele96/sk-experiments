const { combs, perms } = require('../recursion');

describe('recursion', () => {
  test('should return the correct combinations of 1 on list of 3', () => {
    const n = 1;
    const list = [1, 2, 3];
    const result = [[1], [2], [3]];

    expect(combs(n, list)).toEqual(result);
  });

  test('should return the correct combinations of 3 on a list of 5', () => {
    const n = 3;
    const list = [1, 2, 3, 4, 5];
    const result = [
      [1, 2, 3],
      [1, 2, 4],
      [1, 2, 5],
      [1, 3, 4],
      [1, 3, 5],
      [1, 4, 5],
      [2, 3, 4],
      [2, 3, 5],
      [2, 4, 5],
      [3, 4, 5],
    ];

    expect(combs(n, list)).toEqual(result);
  });

  test('should return the correct permutations of 1 on a list of 3', () => {
    const n = 1;
    const list = [1, 2, 3];
    const result = [[1], [2], [3]];

    expect(perms(n, list)).toEqual(result);
  });

  test('should return the correct permutations of 1 on a list of 5', () => {
    const permutations = 1;
    const list = [1, 2, 3, 4, 5];
    const result = [[1], [2], [3], [4], [5]];

    expect(perms(permutations, list)).toEqual(result);
  });

  test('should return the correct permutations of 3 on a list of 3', () => {
    const permutations = 3;
    const list = [1, 2, 3];
    const result = [
      [1, 2, 3],
      [1, 3, 2],
      [2, 1, 3],
      [2, 3, 1],
      [3, 1, 2],
      [3, 2, 1],
    ];

    expect(perms(permutations, list)).toEqual(result);
  });
});
