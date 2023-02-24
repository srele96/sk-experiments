import { Cell } from '../class/Cell';

function createCellGrid(cells) {
  if (typeof cells !== 'number') {
    throw new Error('cells has to be a number');
  }
  if (cells < 0) {
    throw new Error('cells has to be a non negative number');
  }

  const totalSidePercentage = 100;

  function toDecimalPercentage(percent) {
    return percent / totalSidePercentage;
  }

  // Should be less than totalSidePercentage otherwise it doesn't make
  // sense.
  const totalGapPercentage = 20;
  const totalGaps = cells + 1;
  const oneGapPercentage = toDecimalPercentage(totalGapPercentage / totalGaps);
  const totalCellPercentage = totalSidePercentage - totalGapPercentage;
  const oneCellPercentage = toDecimalPercentage(totalCellPercentage / cells);

  function calculateSideOffset(index) {
    const cellAndGap = oneCellPercentage + oneGapPercentage;

    // Append gap before the first cell.
    return cellAndGap * index + oneGapPercentage;
  }

  function calculateOffset(row, col) {
    const xOffset = calculateSideOffset(col);
    const yOffset = calculateSideOffset(row);
    const offset = { xOffset, yOffset };

    return offset;
  }

  const cellGrid = new Array(cells);

  for (let i = 0; i != cells; ++i) {
    cellGrid[i] = new Array(cells);

    for (let j = 0; j != cells; ++j) {
      const { xOffset, yOffset } = calculateOffset(i, j);

      const cell = new Cell(
        xOffset,
        yOffset,
        oneCellPercentage,
        oneCellPercentage
      );

      cellGrid[i][j] = cell;
    }
  }

  return cellGrid;
}

export { createCellGrid };
