const { createElement: e, useEffect } = require('react');
const { Link } = require('react-router-dom');
const { Nav } = require('./Nav');

function Home() {
  useEffect(() => {
    console.log('Home mounted');
  });

  return e('div', null, e(Nav), e('main', null, e('h1', null, 'Home')));
}

export { Home };
