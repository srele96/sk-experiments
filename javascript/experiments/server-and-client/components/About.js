const { createElement: e } = require('react');
const { Nav } = require('./Nav');

function About() {
  return e('div', null, e(Nav), e('main', null, e('h1', null, 'About')));
}

export { About };
