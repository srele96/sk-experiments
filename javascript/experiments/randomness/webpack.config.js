const path = require('path');

/**
 * @type {import('webpack').Configuration}
 */
const config = {
  mode: 'development',
  entry: './src/index.ts',
  output: {
    filename: 'main.js',
    path: path.resolve(__dirname, 'dist'),
  },
  devServer: {
    static: 'public',
  },
  module: {
    rules: [
      {
        test: /\.ts$/,
        use: 'ts-loader',
        exclude: /node_modules/,
      },
    ],
  },
  resolve: {
    // We have to provide '...' before '.ts' because there is an error when
    // starting the app without '...'. I don't remember exactly but I think
    // that '...' mean include extensions you usually would, and '.ts' after
    // adds '.ts' files.
    extensions: ['...', '.ts'],
  },
};

module.exports = config;
