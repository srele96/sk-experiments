const { longest_substring } = require('../longest_substring');

describe('longest_substring', () => {
  test.each([
    ['abcabcbb', 3],
    ['bbbbb', 1],
    ['pw wke w', 4],
    ['123456789', 9],
    ['@a3 456789', 10],
  ])(
    'should return the correct length of the longest substring without ' +
      'repeating characters',
    (string, length) => {
      expect(longest_substring(string)).toEqual(length);
    }
  );
});
