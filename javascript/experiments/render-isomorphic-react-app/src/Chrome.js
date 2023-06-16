// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// IMPORTANT NOTE!
//
// Code in the sample is extremely unreadable.
// Comments explain everything, if not more than they should.
// Aside from that, they probably lack some context.
// I don't want to rethink code to make it more readable.
// I just wanted to go with the flow.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// UNIVERSAL CODE FOR REACT APPLICATION.
// THIS CODE CAN RUN IN NODEJS AND BROWSER.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// i have to declare React and ReactDOM here
// to use different require for browser and the server
let React;
let ReactDOM;

// universal require statements
if (typeof window === 'undefined') {
  // we are on the server
  React = require('react');
  ReactDOM = require('react-dom');
} else {
  // we are on the client
  // take React and ReactDOm from the global window object
  // previous declaration has stomped these
  React = window.React;
  ReactDOM = window.ReactDOM;
}

// a component that proves code is hydrated on the client
function Hydrated() {
  return React.createElement(
    'button',
    { onClick: () => console.log('hydrated') },
    'Hydrated'
  );
}

// wrapper component for the whole page
function Chrome({ children, code, title }) {
  return React.createElement(
    'html',
    null,
    React.createElement(
      'head',
      null,
      React.createElement('title', null, title)
    ),
    React.createElement(
      'body',
      null,
      React.createElement('div', { id: '__root' }, children),
      // provide react to the client
      React.createElement('script', {
        crossOrigin: 'true',
        src: 'https://unpkg.com/react@18/umd/react.development.js',
      }),
      // provide react-dom to the client
      React.createElement('script', {
        crossOrigin: 'true',
        src: 'https://unpkg.com/react-dom@18/umd/react-dom.development.js',
      }),
      // provide code from the server to the client
      // server has to read content of this file and insert it here
      // otherwise it won't be available to the client
      code
    )
  );
}

// universal export and code usage
if (typeof window === 'undefined') {
  // export components if the server requires this file
  // these would throw an error if they are exposed on the client
  // we need these exports to render these components on the server
  module.exports.Chrome = Chrome;
  module.exports.Hydrated = Hydrated;
} else {
  // we are on the client, we have to target root and hydrate the components
  ReactDOM.hydrateRoot(
    document.getElementById('__root'),
    React.createElement(Hydrated)
  );
}
