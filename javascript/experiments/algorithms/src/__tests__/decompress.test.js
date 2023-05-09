const { decompress } = require('../decompress');

describe('decompress', () => {
  const tests = {
    '2[a]': 'aa',
    '2[2[a]]': 'aaaa',
    '0[a]': '',
    'hello3[ab]': 'helloababab',
    '2[a]2[b]': 'aabb',
    '3[b]hello2[a]': 'bbbhelloaa',
    'wtf3[b]': 'wtfbbb',
    '2[hello2[wtf]]': 'hellowtfwtfhellowtfwtf',
    onlystring: 'onlystring',
    'much2[2[2[hey2[b]3[d]]2[c]]]wow':
      'muchheybbdddheybbdddccheybbdddheybbdddccheybbdddheybbdddccheybbdddheybbdddccwow',
    '': '',
  };

  Object.keys(tests).forEach((key) => {
    test(`should correctly decompress ${key}`, () => {
      expect(decompress(key)).toEqual(tests[key]);
    });
  });
});
