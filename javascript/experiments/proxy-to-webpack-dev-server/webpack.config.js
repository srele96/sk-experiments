const ReactRefreshWebpackPlugin = require('@pmmmwh/react-refresh-webpack-plugin');
const { WebpackManifestPlugin } = require('webpack-manifest-plugin');
const path = require('path');

/** @type {import('webpack').Configuration} */
const config = {
  // Don't care to change mode. This is demo.
  mode: 'development',
  entry: path.resolve('client.js'),
  output: {
    path: path.resolve(__dirname, 'public'),
    filename: '[name].[contenthash].js',
    // Remove the public path prefix from WebpackManifestPlugin output.
    publicPath: '',
  },
  // Use optimization to verify that everything works with multiple
  // JavaScript files.
  optimization: {
    runtimeChunk: 'single',
    splitChunks: {
      cacheGroups: {
        vendor: {
          test: /node_modules/,
          name: 'vendors',
          chunks: 'all',
        },
      },
    },
  },
  module: {
    rules: [
      {
        test: /\.js/,
        exclude: /node_modules/,
        use: [
          {
            loader: require.resolve('babel-loader'),
            options: {
              presets: [
                '@babel/preset-env',
                [
                  '@babel/preset-react',
                  {
                    runtime: 'automatic',
                    mode: 'development',
                  },
                ],
              ],
              plugins: [require.resolve('react-refresh/babel')],
            },
          },
        ],
      },
    ],
  },
  devServer: {
    hot: true,
  },
  plugins: [
    new ReactRefreshWebpackPlugin(),
    new WebpackManifestPlugin({
      // Create manifest at runtime.
      writeToFileEmit: true,
    }),
  ],
};

module.exports = config;
