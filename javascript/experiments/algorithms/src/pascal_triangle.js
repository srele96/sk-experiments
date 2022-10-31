// The problem:
//
// Given an integer numRows, return the first numRows of Pascal's triangle.
//
// In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:
//
// Constraints:
//
// 1 <= numRows <= 30

// The solution:
//
// In pascal's triangle, a cell is a sum of two above it.
//
// A cell is identifiable by the column's index. For each row, the columns
// range from the beginning to the end.
//
// It is possible that accessing the two columns above is out of bounds.
//
// If accessing two columns on the top is out of bounds, the current column
// value is 1.
//
// If accessing the previous row is out of bounds, the current value is also 1.
//
// A row has a length equal to its present number.
//
// The first row has one value.
//
// The second row has two values.
//
// The third row has three values.
//
// Each column goes from 1 to row number.
//
// A previous value may underflow or overflow.
//
// Underflow is checkable through minimum column value.
//
// Overflow is checkable by row number, which tells the number of elements.
//
// Check the row for underflow.
//
// Check the column for underflow and overflow.

/**
 * @param {number} rows
 * @return {number[][]}
 */
function pascal_triangle(rows) {
  let row = undefined;
  let column = undefined;

  let columns = undefined;

  let previous_row = undefined;
  let previous_column_left = undefined;
  let previous_column_right = undefined;

  let pascals_triangle = new Array(rows);

  for (row = 0; row < rows; ++row) {
    // The row index starts from 0, but the length of each row begins from 1.
    columns = row + 1;
    pascals_triangle[row] = new Array(columns);

    for (column = 0; column < columns; ++column) {
      previous_row = row - 1;
      previous_column_left = column - 1;
      previous_column_right = column;

      if (
        // Prevent row underflow.
        previous_row > 0 &&
        // Prevent column underflow.
        previous_column_left >= 0 &&
        // Prevent column overflow.
        previous_column_right <= previous_row
      ) {
        pascals_triangle[row][column] =
          pascals_triangle[previous_row][previous_column_left] +
          pascals_triangle[previous_row][previous_column_right];
      } else {
        pascals_triangle[row][column] = 1;
      }
    }
  }

  return pascals_triangle;
}

module.exports.pascal_triangle = pascal_triangle;
