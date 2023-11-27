const { reshape_matrix } = require('../reshape_matrix');

describe('reshape matrix', () => {
  test('should return the original matrix if reshaping is not possible', () => {
    const matrix = [
      [1, 2],
      [3, 4],
    ];
    const rows = 1;
    const columns = 5;

    expect(reshape_matrix(matrix, rows, columns)).toBe(matrix);
  });

  test('should reshape the matrix from 2x2 to 1x4', () => {
    const matrix = [
      [1, 2],
      [3, 4],
    ];
    const rows = 1;
    const columns = 4;
    const reshaped = [[1, 2, 3, 4]];

    expect(reshape_matrix(matrix, rows, columns)).toEqual(reshaped);
  });

  test('should reshape the matrix from 3x3 to 1x9 and 9x1', () => {
    const matrix = [
      [1, 2, 3],
      [4, 5, 6],
      [7, 8, 9],
    ];
    const result_one = {
      rows: 1,
      columns: 9,
      matrix: [[1, 2, 3, 4, 5, 6, 7, 8, 9]],
    };
    const result_two = {
      rows: 9,
      columns: 1,
      matrix: [[1], [2], [3], [4], [5], [6], [7], [8], [9]],
    };

    expect(reshape_matrix(matrix, result_one.rows, result_one.columns)).toEqual(
      result_one.matrix
    );
    expect(reshape_matrix(matrix, result_two.rows, result_two.columns)).toEqual(
      result_two.matrix
    );
  });

  test('should not reshape the matrix from 3x3 to 1x6', () => {
    const matrix = [
      [1, 2, 3],
      [4, 5, 6],
      [7, 8, 9],
    ];
    const rows = 1;
    const columns = 6;

    expect(reshape_matrix(matrix, rows, columns)).toBe(matrix);
  });
});
