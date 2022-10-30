// We can reshape a matrix if the new shape contains the same amount of cells.
//
// The old matrix has R times C amount of items. The new matrix has N times M
// amount of items. If both have an equal amount of items, reshaping is
// possible.
//
// A matrix 3x3 can transform to 1x9 or 9x1.
// A matrix 4x4 can transform to 2x8 or 1x16 or 16x1 or some other.
//
// A transformation happens by iterating through the original matrix, tracking
// the reshaped matrix indices, and copying the items.
//
// On the other hand, we keep track of the matrix using two pointers to its row
// and column.
//
// For each cell in the original matrix, we copy that cell to the reshaped
// matrix and execute the logic to track the indices of the reshaped matrix.
// Reaching columns bound goes to the next row and resets the column to the
// initial one.
//
// After copying the value from the original matrix to the reshaped one,
// execute the logic to track the current indices of the reshaped matrix.
//
// After the execution of logic for each cell, we go to the next column. If a
// column is out of bounds, we must go to the next row in the reshaped matrix
// and reset the column index.
//
// Since old and reshaped matrices have an equal amount of cells, indices above
// the logic to track matrix should always be correct inbound ones.

/**
 * @param {number[][]} mat
 * @param {number} r
 * @param {number} c
 * @return {number[][]}
 */
function reshape_matrix(mat, r, c) {
  let row_length = mat.length;
  let column_length = mat[0].length;

  // Matrix transformation is possible when old and new have an equal amount of elements.
  if (row_length * column_length === r * c) {
    let row = 0;
    let column = 0;
    // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Indexed_collections#multi-dimensional_arrays
    let reshaped_matrix = new Array(r);
    reshaped_matrix[row] = new Array(c);

    // Store original elements to the reshaped matrix.
    for (let i = 0; i != row_length; ++i) {
      for (let j = 0; j != column_length; ++j) {
        reshaped_matrix[row][column] = mat[i][j];

        ++column;
        // Column is out of bounds.
        if (column === c) {
          ++row;
          column = 0;
          // Initialize subsequent rows that are not out of bound.
          if (row !== r) reshaped_matrix[row] = new Array(c);
        }
      }
    }
    return reshaped_matrix;
  } else {
    return mat;
  }
}

module.exports.reshape_matrix = reshape_matrix;
