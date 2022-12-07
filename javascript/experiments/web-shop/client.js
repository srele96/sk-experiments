import { StrictMode } from 'react';
import { hydrateRoot } from 'react-dom/client';

import { App } from './App';

const root = document.querySelector('#root');

// https://github.com/pmmmwh/react-refresh-webpack-plugin/issues/177#issuecomment-718271457
hydrateRoot(
  root,
  <StrictMode>
    <App />
  </StrictMode>
);
