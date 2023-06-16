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

// use arguably more readable asynchronous version of readFile
const { readFile } = require('node:fs/promises');
const path = require('node:path');
// use arguably more readable version of createElement
const { createElement: e } = require('react');
// use recommended react renderer
const { renderToPipeableStream } = require('react-dom/server');
const express = require('express');
// include isomorphic code on the server
const { Chrome, Hydrated } = require('./Chrome');

const app = express();

// read initial request and serve the react app to the client
app.get('/', (_, res) => {
  // read code to serve it on the client to be able to hydrate the app
  readFile(path.join(__dirname, './Chrome.js'), 'utf-8').then((code) => {
    // use new react renderer
    const { pipe } = renderToPipeableStream(
      e(
        // Chrome is a template component that assembles the page
        Chrome,
        {
          // make code accessible so client can use code from Chrome.js
          code: e('script', { dangerouslySetInnerHTML: { __html: code } }),
          title: 'Page',
        },
        // render the page content on the server
        e(Hydrated)
      ),
      {
        onShellReady() {
          // this is the place react suggests to serve the response
          res.setHeader('Content-Type', 'text/html; charset=UTF-8');
          res.status(200);
          pipe(res);
        },
      }
    );
  });
});

app.listen(3000, () => console.log('http://localhost:3000/'));
