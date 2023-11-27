const { pascal_triangle } = require('../pascal_triangle');

describe("pascal's triangle", () => {
  test("should return the correct pascal's triangle with one row", () => {
    const rows = 1;
    const result = [[1]];

    expect(pascal_triangle(rows)).toEqual(result);
  });

  test("should return the correct pascal's triangle with five rows", () => {
    const rows = 5;
    const result = [[1], [1, 1], [1, 2, 1], [1, 3, 3, 1], [1, 4, 6, 4, 1]];

    expect(pascal_triangle(rows)).toEqual(result);
  });

  test("should return the correct pascal's triangle with three rows", () => {
    const rows = 3;
    const result = [[1], [1, 1], [1, 2, 1]];

    expect(pascal_triangle(rows)).toEqual(result);
  });
});
