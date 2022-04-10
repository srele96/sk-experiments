import { lazy } from 'react';
// import and use only cube from math module
// then check if harmony-unused-import is present for square function
import { cube } from './math';
// check if there is any comment present for unused import
import { App } from './App';

// check how does webpack handle code-splitting
import('./Button').then(({ Button }) => {
  console.log(<Button />);
});

// check is there any difference when Reacy.lazy is used
const Button = lazy(() => import('./Button'));

document.body.appendChild(document.createTextNode(`${cube(2)}`));
