import { render, waitFor } from '@testing-library/react';
import { createElement as e } from 'react';
import { App } from './App';

// TODO: https://jestjs.io/docs/expect#expectextendmatchers
// TODO: https://jestjs.io/docs/timer-mocks

// Intellisense for typescript requires explicit import.
// https://jestjs.io/docs/expect#tobevalue

// These are not extended.
// console.log({ describe, expect });

expect.extend({
  toThouShallPass(actual) {
    if (typeof actual !== 'boolean') {
      throw new Error('toThouShallPass expects a boolean');
    }

    return {
      pass: actual,
      message: () => `Thou shall ${actual ? '' : 'not '}pass!`,
    };
  },
  toGetMoar(...args) {
    console.log({ args: JSON.stringify(args) });

    return {
      pass: true,
      message: () => `I got moar!`,
    };
  },
});

// Extended here!
console.log({ expect });

describe('', () => {
  it('should run waitFor many times', async () => {
    render(e(App)); // Do I even need to render?

    let count = 0;

    await expect(
      waitFor(
        () => {
          // screen.debug()

          ++count;

          throw new Error('rerun the waitFor callback');
        },
        { timeout: 1000 }
      )
    ).rejects.toThrow();

    // Allow us to see the count once the test passes.
    console.log(`waitFor ran ${count} times`);
  });

  it('should prove why i can await expect.rejects()', () => {
    return expect(
      new Promise((_, reject) => {
        reject(new Error('lol'));
      })
    ).rejects.toThrow('lol');
  });

  it('should also prove why i can await expect.rejects()', async () => {
    await expect(
      new Promise((_, reject) => {
        reject(new Error('lol'));
      })
    ).rejects.toThrow('lol');
  });

  it('should perform on thou shall pass!', () => {
    expect(true).toThouShallPass();

    expect(false).not.toThouShallPass();
  });

  it('should pass a lot of stuff to get moar!', () => {
    expect({ a: true, b: 'hello' }).toGetMoar('first', 'second', {
      third: [1, 2],
    });
  });
});
