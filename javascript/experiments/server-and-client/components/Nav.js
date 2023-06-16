const { createElement: e } = require('react');
const { Link } = require('react-router-dom');

function Nav() {
  return e(
    'nav',
    null,
    e(
      'ul',
      null,
      e('li', null, e(Link, { to: '/' }, 'Home')),
      e('li', null, e(Link, { to: '/about' }, 'About'))
    )
  );
}

export { Nav };
