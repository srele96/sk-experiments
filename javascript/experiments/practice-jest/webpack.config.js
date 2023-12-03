const HtmlWebpackPlugin = require('html-webpack-plugin');

/**
 * The class to try out a few things with the webpack plugins. I've read that
 * creating webpack plugins require users to read the webpack code to understand
 * the compilation process.
 */
class LearnPlugin {
  pluginName = 'LearnPlugin';

  apply(compiler) {
    compiler.hooks.done.tap(this.pluginName, (stats) => {
      // console.log('LearnPlugin: done');
    });
    compiler.hooks.emit.tap(this.pluginName, (compilation) => {
      // console.log({ assets: Object.keys(compilation.assets) });
      // console.log({ module });
    });
    compiler.hooks.emit.tapAsync(this.pluginName, (compilation, callback) => {
      Object.keys(compilation.assets).forEach((assetName) => {
        if (assetName.endsWith('.js')) {
          const assetContent = compilation.assets[assetName].source();
          // console.log({ assetName, assetContent });
        }
      });
      callback();
    });
  }
}

/** @type {import('webpack').Configuration} */
const config = {
  entry: './entry.js',
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: /node_modules/,
        use: {
          loader: 'babel-loader',
        },
      },
    ],
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: './index.html',
      inject: 'body',
    }),
    new LearnPlugin(),
  ],
};

module.exports = config;
