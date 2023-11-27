import { createElement as e } from 'react';
import reactDOM from 'react-dom/client';
import { App } from './App';

reactDOM.hydrateRoot(document.getElementById('root'), e(App));
