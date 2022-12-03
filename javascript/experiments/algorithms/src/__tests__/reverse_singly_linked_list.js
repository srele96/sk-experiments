const { reverse_singly_linked_list } = require('../reverse_singly_linked_list');

describe('reverse_singly_linked_list', () => {
  test('should reverse two singly linked lists correctly with two consecutive function calls', () => {
    /** @typedef {import('../reverse_singly_linked_list').Node} Node */
    /** @typedef {{ singly_linked_list: Node, singly_reversed_linked_list: Node }} TestSample */

    /** @type {TestSample} */
    const first = {
      singly_linked_list: {
        value: 1,
        next: {
          value: 2,
        },
      },
      reversed_singly_linked_list: {
        value: 2,
        next: {
          value: 1,
          next: null,
        },
      },
    };

    /** @type {TestSample} */
    const second = {
      singly_linked_list: {
        value: 5,
        next: {
          value: 4,
        },
      },
      reversed_singly_linked_list: {
        value: 4,
        next: {
          value: 5,
          next: null,
        },
      },
    };

    expect(reverse_singly_linked_list()(first.singly_linked_list)).toEqual(
      first.reversed_singly_linked_list
    );
    expect(reverse_singly_linked_list()(second.singly_linked_list)).toEqual(
      second.reversed_singly_linked_list
    );
  });
});
