// IMPORTANT!
//
// Don't wrap in IIFE - Immediately Invoked Function Expression to preserve
// these values as global utilities.

// TODO(reuse types): Find a way to reuse types across multiple files.

/**
 * @param {number} degree
 */
function radians(degree) {
  return degree * (Math.PI / 180);
}

/**
 * @typedef {Object} Point
 * @property {number} Point.x
 * @property {number} Point.y
 */

/**
 * @param {Object} options
 * @param {Point} options.from
 * @param {number} options.angle
 * @param {number} options.length
 */
function point({ from, angle, length }) {
  const angleInRadians = radians(angle);

  return {
    x: from.x + length * Math.cos(angleInRadians),
    y: from.y + length * Math.sin(angleInRadians),
  };
}
