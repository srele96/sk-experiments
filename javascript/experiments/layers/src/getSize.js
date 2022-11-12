/**
 * @typedef {Object} Size
 * @property {number} Size.layerWidth
 * @property {number} Size.containerWidth
 * @property {number} Size.containerHeight
 */

/**
 * @returns {Size}
 */
function getSize() {
  // Divide the window width by a value more significant than the multiplier
  // because all my moving logic relies on the layer's width.
  const layerWidth = window.innerWidth / 4;

  const sixByTenPercentToSide = 1.6;
  const containerWidth = sixByTenPercentToSide * layerWidth;

  const largerThanWidth = 1.5;
  const containerHeight = largerThanWidth * layerWidth;

  return { layerWidth, containerWidth, containerHeight };
}

export { getSize };