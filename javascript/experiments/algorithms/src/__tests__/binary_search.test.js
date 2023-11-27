const { binary_search } = require('../binary_search');

describe('binary_search', () => {
  let numbers;
  let begin;
  let end;

  beforeEach(() => {
    numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9];
    begin = 0;
    end = numbers.length - 1;
  });

  afterEach(() => {
    numbers = undefined;
    begin = undefined;
    end = undefined;
  });

  test(
    'should return the correct indicator that' +
      " the algorithm didn't find the number",
    () => {
      const value = 15;
      const index = -1;

      expect(binary_search(numbers, begin, end, value)).toEqual(index);
    }
  );

  test(
    'should return the valid index when the' +
      ' number is to the right of the center',
    () => {
      const value = 8;
      const index = 7;

      expect(binary_search(numbers, begin, end, value)).toEqual(index);
    }
  );

  test(
    'should return the valid index when the' +
      ' number is to the left of the center',
    () => {
      const value = 3;
      const index = 2;

      expect(binary_search(numbers, begin, end, value)).toEqual(index);
    }
  );
});
