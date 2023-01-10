const commonjs = require('@rollup/plugin-commonjs');
const { defineConfig } = require('rollup');
const path = require('path');

const packageJson = require('./package.json');

module.exports = defineConfig({
  input: path.resolve(__dirname, 'src', 'index.js'),
  output: {
    dir: 'dist',
    format: 'umd',
    name: packageJson.name,
  },
  plugins: [
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Temporary patch because rollup doesn't support commonjs natively.
    // I don't want to use ES modules because I need a prototype that I can
    // write with as little tools as possible. On the other side, I couldn't
    // use ES modules because Jest doesn't support them natively.
    commonjs(),
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ],
});
