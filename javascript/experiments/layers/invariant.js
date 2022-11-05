'use strict';

const invariant = Object.freeze({
  validOptions: Object.freeze(function (options, validOptions) {
    const hasValidOptions =
      options &&
      Object.keys(options).length === validOptions.length &&
      Object.keys(options).every((option) => validOptions.includes(option));

    if (!hasValidOptions) {
      throw new Error(
        'received invalid options, valid options are: ' +
          validOptions.join(', ')
      );
    }
  }),
  validNumbers: Object.freeze(function (...numbers) {
    if (!numbers.every((number) => Number.isFinite(number))) {
      throw new Error('received invalid numbers');
    }
  }),
  validArray: Object.freeze(function (array) {
    if (!Array.isArray(array)) {
      throw new Error('received unexpected type, expected array');
    }
  }),
  lengthEqualOrLess: Object.freeze(function (array, length) {
    if (array.length > length) {
      throw new Error(
        'expected an array to have equal or smaller length than ' + length
      );
    }
  }),
});
