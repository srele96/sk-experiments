/**
 * @typedef {Object} Size
 * @property {number} Size.layerWidth
 * @property {number} Size.containerWidth
 * @property {number} Size.containerHeight
 */

/**
 * @typedef {Object} Space
 * @property {string} Space.moveFromTopLayer
 * @property {string | undefined} Space.moveToTopLayer
 * @property {string} Space.scale
 * @property {number} Space.zIndex
 */

/**
 * @typedef {Object.<number, Space>} Spaces
 */

/**
 * @returns {number}
 */
function getLayerWidth() {
  // Divide the window width by a value more significant than the multiplier
  // because all my moving logic relies on the layer's width.
  return window.innerWidth / 4;
}

/**
 * @returns {Size}
 */
function getSizeForLayersSpacedAroundTopLayer() {
  const layerWidth = getLayerWidth();

  // Six layers visible 10% of the 100% size of top layer.
  // Two times 80% size around the top layer.
  // 6 * 10 + 100 + 2 * 80 = 320
  const widthMultiplier = 3.2;
  const containerWidth = widthMultiplier * layerWidth;

  const heightMultiplier = 1.5;
  const containerHeight = heightMultiplier * layerWidth;

  return { layerWidth, containerWidth, containerHeight };
}

/**
 * @param {number} by
 * @returns {string}
 */
function translateX(by) {
  return `translateX(${by}%)`;
}

/**
 * @param {number} by
 * @returns {string}
 */
function scale(by) {
  return `scale(${by})`;
}

// prettier-ignore
/**
 * @type {Spaces}
 */
const spaceAroundToplayer = {
  [-6]: { moveFromTopLayer: translateX(-175), scale: scale(0.3), zIndex: 1, moveToTopLayer: translateX(140), },
  [-5]: { moveFromTopLayer: translateX(-160), scale: scale(0.4), zIndex: 2, moveToTopLayer: translateX(130), },
  [-4]: { moveFromTopLayer: translateX(-145), scale: scale(0.5), zIndex: 3, moveToTopLayer: translateX(120), },
  [-3]: { moveFromTopLayer: translateX(-130), scale: scale(0.6), zIndex: 4, moveToTopLayer: translateX(110), },
  [-2]: { moveFromTopLayer: translateX(-115), scale: scale(0.7), zIndex: 5, moveToTopLayer: translateX(100), },
  [-1]: { moveFromTopLayer: translateX(-100), scale: scale(0.8), zIndex: 6, moveToTopLayer: translateX( 90), },

  // The top layer can be anywhere from first to last.
  // Always take one of the first seven from here as the first.
  // The first element stores the information of where the top layer is.
  [ 0]: { moveFromTopLayer: translateX(   0), scale: scale(1.0), zIndex: 7, moveToTopLayer: translateX(  0), },

  [ 1]: { moveFromTopLayer: translateX( 100), scale: scale(0.8), zIndex: 6, moveToTopLayer: undefined        },
  [ 2]: { moveFromTopLayer: translateX( 115), scale: scale(0.7), zIndex: 5, moveToTopLayer: undefined        },
  [ 3]: { moveFromTopLayer: translateX( 130), scale: scale(0.6), zIndex: 4, moveToTopLayer: undefined        },
  [ 4]: { moveFromTopLayer: translateX( 145), scale: scale(0.5), zIndex: 3, moveToTopLayer: undefined        },
  [ 5]: { moveFromTopLayer: translateX( 160), scale: scale(0.4), zIndex: 2, moveToTopLayer: undefined        },
  [ 6]: { moveFromTopLayer: translateX( 175), scale: scale(0.3), zIndex: 1, moveToTopLayer: undefined        },
};

export { spaceAroundToplayer, getSizeForLayersSpacedAroundTopLayer };
