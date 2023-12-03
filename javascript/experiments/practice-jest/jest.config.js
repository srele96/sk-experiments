/** @type {import('jest').Config} */
const config = {
  moduleFileExtensions: ['js'],
  transform: {
    // only files that end with .js because jest can't handle es6 modules.
    '^.+\\.js$': 'babel-jest',
  },
  // @testing-library/react fails without this.
  // Requires the `jest-environment-jsdom` to be installed.
  testEnvironment: 'jsdom',
  // Don't import it manually in every test file.
  setupFilesAfterEnv: ['@testing-library/jest-dom'],
};

module.exports = config;
