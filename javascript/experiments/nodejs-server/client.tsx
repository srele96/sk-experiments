import { hydrateRoot } from 'react-dom/client';
import { App } from './App';

const root = document.querySelector('#root');
if (!root) {
  throw new Error('Document root missing!');
}

hydrateRoot(root, <App />);
