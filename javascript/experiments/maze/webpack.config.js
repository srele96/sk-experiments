const path = require('path');

/**
 * @type {import('webpack').Configuration}
 */
const config = {
  mode: 'development',
  entry: path.join(__dirname, 'src', 'entry.js'),
  output: {
    path: path.join(__dirname, 'dist'),
    filename: 'bundle.js',
  },
  devServer: {
    static: 'public',
    port: 3000,
  },
};

module.exports = config;
