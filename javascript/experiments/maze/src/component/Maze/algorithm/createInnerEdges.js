import { Edge } from '../class/Edge';
import { Cell } from '../class/Cell';

function createInnerEdges(cellGrid) {
  let edges = [];

  function createVertex(row, column) {
    return ''.concat(row, column);
  }

  function oneLess(value) {
    return value - 1;
  }

  function exist(index) {
    return index > -1;
  }

  function reduceByHalfLength(offset, length) {
    return offset - length / 2;
  }

  function createEdgeData(cells, row) {
    cells.forEach((cell, column) => {
      const currentVertex = createVertex(row, column);

      const leftColumn = oneLess(column);
      if (exist(leftColumn)) {
        const leftVertex = createVertex(row, leftColumn);
        const xOffset = reduceByHalfLength(cell.xOffset, cell.width);
        const edgeCell = new Cell(
          xOffset,
          cell.yOffset,
          cell.width,
          cell.height
        );
        const edge = new Edge(leftVertex, currentVertex, edgeCell);

        edges.push(edge);
      }

      const topRow = oneLess(row);
      if (exist(topRow)) {
        const topVertex = createVertex(topRow, column);
        const yOffset = reduceByHalfLength(cell.yOffset, cell.height);
        const edgeCell = new Cell(
          cell.xOffset,
          yOffset,
          cell.width,
          cell.height
        );
        const edge = new Edge(topVertex, currentVertex, edgeCell);

        edges.push(edge);
      }
    });
  }

  cellGrid.forEach(createEdgeData);

  return edges;
}

export { createInnerEdges };
