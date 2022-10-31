// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// The problem
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be
// validated according to the following rules:
//
//     Each row must contain the digits 1-9 without repetition.
//     Each column must contain the digits 1-9 without repetition.
//     Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
//
// Note:
//
//     A Sudoku board (partially filled) could be valid but is not necessarily solvable.
//     Only the filled cells need to be validated according to the mentioned rules.
//
// Constraints:
//
// board.length == 9
// board[i].length == 9
// board[i][j] is a digit 1-9 or '.'.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// The solution
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Use a hash map for each row and column with unique values and their count.
//
// I can determine if a value exists if I remember how many times I have seen
// it or use a boolean.
//
// How do I keep track of each nine 3x3 sub-boxes?
//
// Each of the nine 3x3 sub-boxes must contain 1 to 9 inclusive digits.
//
// If I am inside a box, I must check if the current value matches any existing
// ones.
//
// Column and row are rules for the whole grid.
//
// Checking if I am in the box requires row and column indices.
//
// The first box contains row indices below or equal to 2 and column indices
// below or equal to 2.
//
// Draw the matrix and extract rules for each box.
//
// One way is to write rules for each row and column, but that is not viable.
//
// A few of the rules are rules are:
//  - top-left rule: column <= 2 && row <= 2
//  - top-center rule: column >=3 && column <= 5 && row <= 2
//  - top-right rule: column >= 6 && row <= 2
//  - left-center rule: col <= 2 && row >= 3 && row <= 5
//  - center-center rule: col >= 3 && col <= 5 && row >= 3 && row <= 5
//
// After reducing those conditions to common ones, I have:
//  - below: value <= 2
//  - between: value >= 3 && value <= 5
//  - above: value >= 6
//
// That means I have a table like this:
//  - below(row) && below(column) yields top left
//  - below(row) && between(column) yields top center
//  - below(row) && above(column) yields top right
//
// That allowed me to combine them.
//
// After that, I could assign indices to each sub-box.
//
//  - top-left sub-box had an index of 0
//  - top-center sub-box had index 1
//  - top-right sub-box had index 2
//
// The indices for each box ranged from 0 to 9 inclusive.
//
// Each sub-box must have unique values ranging from 1 to 9 inclusive.
//
// Each cell is a number from 1 to 9 inclusive.
//
// Each cell should ignore the character that indicates the cell is empty.
//
// For each cell, verify that each of the rules holds.
//
// The loop's role is to terminate and exit the function if the table is
// invalid. In other words, the loop should check for broken rules and
// terminate, indicating an invalid sudoku table. On the other hand, an
// unterminated loop means the sudoku table is valid.
//
// Each row knows its values.
//
// Each column knows its values.
//
// Each sub-box knows its values.
//
// We can break down the problem as follows:
//  - Ignore empty cell
//  - Check if the value has been seen and terminate if that holds true
//  - Otherwise, mark the value as already seen
//
// Each cell belongs to each of the rules.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Bounds
const below /*************/ = (value) => value <= 2;
const between /***********/ = (value) => value >= 3 && value <= 5;
const above /*************/ = (value) => value >= 6;
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Rules
const is_top_left /*******/ = (row, column) => below(row) && below(column);
const is_top_center /*****/ = (row, column) => below(row) && between(column);
const is_top_right /******/ = (row, column) => below(row) && above(column);

const is_center_left /****/ = (row, column) => between(row) && below(column);
const is_center_center /**/ = (row, column) => between(row) && between(column);
const is_center_right /***/ = (row, column) => between(row) && above(column);

const is_bottom_left /****/ = (row, column) => above(row) && below(column);
const is_bottom_center /**/ = (row, column) => above(row) && between(column);
const is_bottom_right /***/ = (row, column) => above(row) && above(column);
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const box = {
  top_left: 0,
  top_center: 1,
  top_right: 2,
  center_left: 3,
  center_center: 4,
  center_right: 5,
  bottom_left: 6,
  bottom_center: 7,
  bottom_right: 8,
};

function get_box(row, column) {
  if (is_top_left(row, column)) {
    return box.top_left;
  } else if (is_top_center(row, column)) {
    return box.top_center;
  } else if (is_top_right(row, column)) {
    return box.top_right;
  } else if (is_center_left(row, column)) {
    return box.center_left;
  } else if (is_center_center(row, column)) {
    return box.center_center;
  } else if (is_center_right(row, column)) {
    return box.center_right;
  } else if (is_bottom_left(row, column)) {
    return box.bottom_left;
  } else if (is_bottom_center(row, column)) {
    return box.bottom_center;
  } else if (is_bottom_right(row, column)) {
    return box.bottom_right;
  } else {
    throw new Error('Check your code. I should not happen.');
  }
}

/**
 * @param {character[][]} board
 * @return {boolean}
 */
function valid_sudoku(board) {
  const row_history = new Map();
  const column_history = new Map();
  const box_history = new Map();

  // Fixate the board size for efficiency.
  // LeetCode constraints allow me to do that.
  const board_size = 9;

  const ignore_cell = '.';
  const remember_the_value = true;
  const invalid_board = false;

  let current_row = undefined;
  let current_column = undefined;
  let current_box = undefined;

  let cell = undefined;
  let count = undefined;

  // Initialize histories.
  for (let i = 0; i != board_size; ++i) {
    // Each key marks a row where each value should be unique.
    row_history.set(i, new Map());
    // Each key marks a column where each value should be unique.
    column_history.set(i, new Map());
    // Each key marks a box where each value should be unique.
    box_history.set(i, new Map());
  }

  // Terminate if sudoku board is invalid.
  for (let row = 0; row != board_size; ++row) {
    for (let column = 0; column != board_size; ++column) {
      cell = board[row][column];

      if (cell !== ignore_cell) {
        current_row = row_history.get(row);
        if (current_row.has(cell)) {
          return invalid_board;
        } else {
          current_row.set(cell, remember_the_value);
        }

        current_column = column_history.get(column);
        if (current_column.has(cell)) {
          return invalid_board;
        } else {
          current_column.set(cell, remember_the_value);
        }

        current_box = box_history.get(get_box(row, column));
        if (current_box.has(cell)) {
          return invalid_board;
        } else {
          current_box.set(cell, remember_the_value);
        }
      }
    }
  }

  // Sudoku board is valid.
  return true;
}

module.exports.valid_sudoku = valid_sudoku;
