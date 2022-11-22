import { StrictMode } from 'react';
import { createRoot } from 'react-dom/client';

function App() {
  return <h1>An App!</h1>;
}

const root = document.querySelector('#my_root');

createRoot(root).render(
  <StrictMode>
    <App />
  </StrictMode>
);
