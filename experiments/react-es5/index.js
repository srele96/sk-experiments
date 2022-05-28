var e = React.createElement;

// Notes for reader:
//   - closures used to reuse same variable names in each example
//   - this example demonstrates usage of multiple roots
//   - this example assumes you know how to use React with ES6/JSX

// ----------------------------------------------------------------------------
// Example 1:
// How to render application

/**
 * Renders main headline.
 */
(function () {
  function App() {
    return e('h1', null, 'How to render application');
  }

  var root = ReactDOM.createRoot(document.getElementById('example1'));
  root.render(e(App));
})();

// ----------------------------------------------------------------------------
// Example 2:
// How to use props

/**
 * Renders user with given name.
 */
(function () {
  function User(props) {
    return e('h2', null, 'Hello ' + props.name);
  }

  function App() {
    return e(
      'div',
      null,
      e('h1', null, 'How to use props'),
      e(User, { name: 'John' })
    );
  }

  var root = ReactDOM.createRoot(document.getElementById('example2'));
  root.render(e(App));
})();

// ----------------------------------------------------------------------------
// Example 3:
// How to use state

/**
 * Renders counter value and two buttons to increment and decrement counter.
 */
(function () {
  function Counter() {
    var counter = React.useState(0);
    var count = counter[0];
    var setCount = counter[1];

    function increment() {
      setCount(function (previousCount) {
        return previousCount + 1;
      });
    }

    function decrement() {
      setCount(function (previousCount) {
        return previousCount - 1;
      });
    }

    return e(
      'div',
      null,
      e('button', { onClick: increment }, 'Increment'),
      e('button', { onClick: decrement }, 'Decrement'),
      e('h2', null, 'Counter value:' + count)
    );
  }

  function App() {
    return e('div', null, e('h1', null, 'How to use state'), e(Counter));
  }

  var root = ReactDOM.createRoot(document.getElementById('example3'));
  root.render(e(App));
})();

// ----------------------------------------------------------------------------
// Example 4:
// How to use children

/**
 * Renders list of vegetables.
 */
(function () {
  function UnorderedList(props) {
    return e('ul', null, props.children);
  }

  function App() {
    return e(
      'div',
      null,
      e('h1', null, 'How to use children'),
      e(
        UnorderedList,
        null,
        e('li', null, 'Carrots'),
        e('li', null, 'Tomatoes')
      )
    );
  }

  var root = ReactDOM.createRoot(document.getElementById('example4'));
  root.render(e(App));
})();

// ----------------------------------------------------------------------------
// Example 5:
// How to pass attribute to elements

/**
 * Renders div with data-id attribute.
 */
(function () {
  function App() {
    return e(
      'div',
      null,
      e('h1', null, 'How to pass attribute to elements'),
      e('div', { 'data-id': 1 }, 'div with data-id 1')
    );
  }

  var root = ReactDOM.createRoot(document.getElementById('example5'));
  root.render(e(App));
})();

// ----------------------------------------------------------------------------
// Example 6:
// How to use useEffect

/**
 * Renders initial text and changes it 1s after first render.
 */
(function () {
  function App() {
    var _text = React.useState('initial text');
    var text = _text[0];
    var setText = _text[1];

    React.useEffect(function () {
      setTimeout(function () {
        setText('changed after 1s from useEffect');
      }, 1000);
    });

    return e(
      'div',
      null,
      e('h1', null, 'How to use useEffect'),
      e('h2', null, text)
    );
  }

  var root = ReactDOM.createRoot(document.getElementById('example6'));
  root.render(e(App));
})();

// Bonus examples:

// ----------------------------------------------------------------------------
// Example 7:
// More readable event handler callbacks - `onClick={remove(1)}`
// Note: example is written using es5, but is same for es6 - just shorter

(function () {
  function App() {
    function remove(id) {
      return function onClick(event) {
        console.log(id, event);
      };
    }

    return e(
      'div',
      null,
      e(
        'h1',
        null,
        'More readable event handler callbacks - `onClick={remove(1)}`'
      ),
      // remove is immediately invoked when passed to button
      // it returns onClick function which handles event
      e('button', { onClick: remove(1) }, 'Change text')
    );
  }

  var root = ReactDOM.createRoot(document.getElementById('example7'));
  root.render(e(App));
})();
