'use strict';

function get_elements(options) {
  if (!options) {
    throw new Error('options are required');
  }
  if (!Number.isFinite(options.length)) {
    throw new Error(
      'length must be a number, received ' + typeof options.length
    );
  }

  return function (main_element) {
    if (typeof main_element !== 'number') {
      throw new Error(
        'main_element must be a number, received ' + typeof main_element
      );
    }
    if (main_element < 1 || main_element > options.length) {
      throw new Error('main_element out of range');
    }

    let elements = new Array(options.length);
    const main_element_index = main_element - 1;

    for (let i = 0; i != elements.length; ++i) {
      const element = {
        order: i - main_element_index,
      };

      elements[i] = options.callback ? options.callback(element) : element;
    }

    return elements;
  };
}

module.exports.get_elements = get_elements;
