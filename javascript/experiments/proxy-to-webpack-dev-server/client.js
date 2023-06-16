import { StrictMode } from 'react';
import { createRoot } from 'react-dom/client';

import { App } from './App';

const root = document.querySelector('#my_root');

// https://github.com/pmmmwh/react-refresh-webpack-plugin/issues/177#issuecomment-718271457
createRoot(root).render(
  <StrictMode>
    <App />
  </StrictMode>
);
