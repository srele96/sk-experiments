import { createElement as e, StrictMode } from 'react';
import { createRoot } from 'react-dom/client';
import { App } from './component/App';

function renderApp() {
  const id = 'app';
  const domRoot = document.getElementById(id);

  createRoot(domRoot).render(e(StrictMode, null, e(App)));
}

renderApp();
