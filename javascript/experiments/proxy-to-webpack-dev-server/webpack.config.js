const path = require('path');

/** @type {import('webpack').Configuration} */
const config = {
  entry: 'client.js',
  // Use the same directory as the express server.
  output: {
    path: path.resolve(__dirname, 'public'),
    filename: 'bundle.js',
  },
};

module.exports = config;
