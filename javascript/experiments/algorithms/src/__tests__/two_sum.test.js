const { two_sum } = require('../two_sum');

test('should return the correct indices for case 1', () => {
  const numbers = [2, 7, 11, 15];
  const target = 9;
  const indices = [0, 1];

  expect(two_sum(numbers, target)).toEqual(indices);
});

test('should return the correct indices for case 2', () => {
  const numbers = [3, 2, 4];
  const target = 6;
  const indices = [1, 2];

  expect(two_sum(numbers, target)).toEqual(indices);
});

test('should return the correct indices for case 3', () => {
  const numbers = [3, 3];
  const target = 6;
  const indices = [0, 1];

  expect(two_sum(numbers, target)).toEqual(indices);
});
