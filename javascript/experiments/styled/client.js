import { createElement as e } from 'react';
import { hydrateRoot } from 'react-dom/client';
import { App } from './App';

hydrateRoot(document.getElementById('root'), e(App));
