const { max_profit } = require('../max_profit');

test('should calculate the correct profit when there is one', () => {
  const case_one = {
    prices: [7, 1, 5, 3, 6, 4],
    profit: 5,
  };

  const case_two = {
    prices: [2, 4, 1],
    profit: 2,
  };

  expect(max_profit(case_one.prices)).toEqual(case_one.profit);
  expect(max_profit(case_two.prices)).toEqual(case_two.profit);
});

test('should return zero profit when there is none', () => {
  const prices = [7, 6, 4, 3, 1];
  const profit = 0;

  expect(max_profit(prices)).toEqual(profit);
});
