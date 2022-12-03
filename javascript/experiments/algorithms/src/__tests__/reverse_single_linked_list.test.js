const { reverse_single_linked_list } = require('../reverse_single_linked_list');

describe('reverse_single_linked_list', () => {
  test('should reverse two single-linked lists correctly with two consecutive function calls', () => {
    /** @typedef {import('../reverse_single_linked_list').Node} Node */
    /** @typedef {{ single_linked_list: Node, reversed_single_linked_list: Node }} TestSample */

    /** @type {TestSample} */
    const first = {
      single_linked_list: {
        value: 1,
        next: {
          value: 2,
        },
      },
      reversed_single_linked_list: {
        value: 2,
        next: {
          value: 1,
          next: null,
        },
      },
    };

    /** @type {TestSample} */
    const second = {
      single_linked_list: {
        value: 5,
        next: {
          value: 4,
        },
      },
      reversed_single_linked_list: {
        value: 4,
        next: {
          value: 5,
          next: null,
        },
      },
    };

    expect(reverse_single_linked_list()(first.single_linked_list)).toEqual(
      first.reversed_single_linked_list
    );
    expect(reverse_single_linked_list()(second.single_linked_list)).toEqual(
      second.reversed_single_linked_list
    );
  });
});
