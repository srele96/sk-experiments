import('./foo').then((value) => {
  console.log(value.default());
});

import('./baz').then((value) => {
  console.log(value.default());
});

import { bar } from './bar';
console.log(bar());

import { createElement as e } from 'react';
import { createRoot } from 'react-dom/client';
import Qux from './Qux';
createRoot(document.getElementById('qux')).render(e(Qux));
