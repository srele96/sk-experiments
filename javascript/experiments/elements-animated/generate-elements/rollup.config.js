/**
 * Use config file from: https://github.com/srele96/elements/tree/main
 *
 * https://github.com/srele96/elements/blob/main/rollup.config.js
 */

const commonjs = require('@rollup/plugin-commonjs');
const { defineConfig } = require('rollup');
const path = require('path');

const packageJson = require('./package.json');

function removeScope(name) {
  const scopeSymbol = /^@/;
  const emptySpace = '';

  return name.replace(scopeSymbol, emptySpace);
}

function toDashCase(name) {
  const firstSlash = /\//;
  const dash = '-';

  return removeScope(name).replace(firstSlash, dash);
}

function toCamelCase(name) {
  const firstSlash = /\//;
  const dash = '-';

  function capitalizeWords(word) {
    const firstLetter = 0;
    const excludeFirstLetter = 1;
    const capitalizedWord =
      word.charAt(firstLetter).toUpperCase() + word.slice(excludeFirstLetter);

    return capitalizedWord;
  }
  const emptySpace = '';

  return removeScope(name)
    .replace(firstSlash, dash)
    .split(dash)
    .map(capitalizeWords)
    .join(emptySpace);
}

module.exports = defineConfig({
  input: path.resolve(__dirname, 'index.js'),
  output: {
    file: `dist/${toDashCase(packageJson.name)}.umd.js`,
    format: 'umd',
    name: toCamelCase(packageJson.name),
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
