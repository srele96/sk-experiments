const { combs, perms, gcd, reverse } = require('../recursion');

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

  test('should return the correct greatest common divisor of 2 and 4', () => {
    const larger = 4;
    const smaller = 2;
    const result = 2;

    expect(gcd(larger, smaller)).toEqual(result);
  });

  test('should return the correct greatest common divisor of 21 and 42', () => {
    const larger = 42;
    const smaller = 21;
    const result = 21;

    expect(gcd(larger, smaller)).toEqual(result);
  });

  test('should return the correct greatest common divisor of 10 and 45', () => {
    const larger = 45;
    const smaller = 10;
    const result = 5;

    expect(gcd(larger, smaller)).toEqual(result);
  });

  test('should reverse the string "hello"', () => {
    const string = 'hello';
    const reversed = 'olleh';

    expect(reverse(string)).toEqual(reversed);
  });

  test('should reverse the string "hello world"', () => {
    const string = 'hello world';
    const reversed = 'dlrow olleh';

    expect(reverse(string)).toEqual(reversed);
  });

  test('should reverse the palindrome "racecar"', () => {
    const palindrome = 'racecar';

    // Should equal to itself.
    expect(reverse(palindrome)).toEqual(palindrome);
  });
});
