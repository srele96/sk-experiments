import { createElement as e } from 'react';

import { Canvas } from '../Canvas';

import { createCellGrid } from './createCellGrid';
import { createInnerEdges } from './createInnerEdges';
import { createMazePath } from './createMazePath';

function Maze(props) {
  const width = props.side;
  const height = props.side;

  function drawMaze(ctx) {
    const xOffset = 0;
    const yOffset = 0;

    ctx.clearRect(xOffset, yOffset, width, height);
    ctx.beginPath();

    const gapColor = 'black';
    ctx.fillStyle = gapColor;

    ctx.fillRect(xOffset, yOffset, width, height);

    function toValue(cell) {
      const value = {
        xOffset: cell.xOffset * width,
        yOffset: cell.yOffset * height,
        width: cell.width * width,
        height: cell.height * height,
      };

      return value;
    }

    function fillCell(cell) {
      const { xOffset, yOffset, width, height } = toValue(cell);
      ctx.fillRect(xOffset, yOffset, width, height);
    }

    const cellGrid = createCellGrid(props.cells);

    const cellColor = 'white';
    ctx.fillStyle = cellColor;
    cellGrid.forEach((cells) => cells.forEach(fillCell));

    const innerEdges = createInnerEdges(cellGrid);
    innerEdges.sort((one, two) => one.weight - two.weight);
    createMazePath(innerEdges, fillCell);

    ctx.closePath();
    ctx.stroke();
  }

  return e(Canvas, {
    width,
    height,
    onContext2d: drawMaze,
  });
}

export { Maze };
