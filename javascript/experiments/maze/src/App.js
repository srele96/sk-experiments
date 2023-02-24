import { createElement as e } from 'react';
import { Maze } from './Maze';

function App() {
  const side = 300;
  const cells = 10;

  return e(Maze, { side, cells });
}

export { App };
