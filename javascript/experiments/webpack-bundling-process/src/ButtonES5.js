import React from 'react';

// check how does webpack handle this type of code, is it transpiled?
function ButtonES5({ text, onClick }) {
  return React.createElement('button', { onClick }, text);
}

export { ButtonES5 };
