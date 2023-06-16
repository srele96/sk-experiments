// The job of this file is to set up @babel/register compilation.
// Babel register hooks in nodejs require function to compile fles.
// That means this file is never compiled.
// That's why we use this file as compilation entry point.

// Set up babel compilation before anything else.
require('@babel/register')({
  presets: [
    '@babel/preset-env',
    ['@babel/preset-react', { runtime: 'automatic' }],
  ],
});

// Compile subsequent files.
require('./src/server.js');
