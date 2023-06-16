const MiniCssExtractPlugin = require('mini-css-extract-plugin');

/** @type {import('webpack').Configuration} */
const config = {
  entry: './client.js',
  mode: 'development',
  output: {
    filename: 'client.js',
  },
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: /node_modules/,
        use: {
          loader: require.resolve('babel-loader'),
          options: {
            presets: [
              '@babel/preset-env',
              [
                '@babel/preset-react',
                {
                  runtime: 'automatic',
                },
              ],
            ],
          },
        },
      },
      {
        test: /\.css$/i,
        use: [
          require.resolve('isomorphic-style-loader'),
          {
            loader: require.resolve('css-loader'),
            options: {
              modules: true,
            },
          },
        ],
      },
    ],
  },
  // provide readable output
  devtool: false,
};

module.exports = config;
