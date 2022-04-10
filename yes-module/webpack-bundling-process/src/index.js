import { lazy } from 'react';
// import and use only cube from math module
// then check if harmony-unused-import is present for square function
import { cube } from './math';
// check if there is any comment present for unused import
import { App } from './App';
import { ButtonES5 } from './ButtonES5';

// check how does webpack handle code-splitting
import('./Button').then(({ Button }) => {
  console.log(<Button />);
});

// check is there any difference when Reacy.lazy is used
const Button = lazy(() => import('./Button'));

// check is it possible to use jsx syntax on
// button created with create.element function
console.log(<ButtonES5 />);

document.body.appendChild(document.createTextNode(`${cube(2)}`));
