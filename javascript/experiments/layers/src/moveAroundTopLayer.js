/**
 * @typedef {Object} Data
 * @property {string} Data.src
 * @property {string} Data.alt
 */

/**
 * @typedef {Object} Layer
 * @property {string} Layer.moveFromTopLayer
 * @property {string} Layer.moveToTopLayer
 * @property {string} Layer.scale
 * @property {number} Layer.zIndex
 * @property {Data} Layer.data
 */

/** @type {Layer[]} */
const moveAroundTopLayer = [
  {
    moveFromTopLayer: 'translateX(-50%)',
    moveToTopLayer: 'translateX(20%)',
    scale: 'scale(0.6)',
    zIndex: 4,
    data: {
      src: 'https://i.pinimg.com/564x/2f/19/aa/2f19aad54ba05a5ebd5e7852e10852c3.jpg',
      alt: 'Half Denji transformed into the chainsaw man and half Denji.',
    },
  },
  {
    moveFromTopLayer: 'translateX(-35%)',
    moveToTopLayer: 'translateX(20%)',
    scale: 'scale(0.7)',
    zIndex: 5,
    data: {
      src: 'https://i.pinimg.com/564x/b6/a9/39/b6a939a9456ec3eb1dd95363d55a97f8.jpg',
      alt: 'Makima is wearing the suit and looking to her side.',
    },
  },
  {
    moveFromTopLayer: 'translateX(-20%)',
    moveToTopLayer: 'translateX(20%)',
    scale: 'scale(0.8)',
    zIndex: 6,
    data: {
      src: 'https://i.pinimg.com/564x/aa/8f/10/aa8f1009a94ccf7b6580970ac2b85439.jpg',
      alt: 'Makima reaches her hand out to Denji, transformed into the chainsaw man.',
    },
  },
  {
    moveFromTopLayer: 'translateX(0%)',
    moveToTopLayer: 'translateX(20%)',
    scale: 'scale(1)',
    zIndex: 7,
    data: {
      src: 'https://i.pinimg.com/564x/19/f1/63/19f1633e1c8f8e9ac16b45ea1a187ae4.jpg',
      alt: 'Power holding two fingers up.',
    },
  },
  {
    moveFromTopLayer: 'translateX(20%)',
    moveToTopLayer: 'translateX(20%)',
    scale: 'scale(0.8)',
    zIndex: 6,
    data: {
      src: 'https://i.pinimg.com/564x/43/61/75/436175e69b591504d34d94e93f84c136.jpg',
      alt: 'Power looked back from her side with a serious look.',
    },
  },
  {
    moveFromTopLayer: 'translateX(35%)',
    moveToTopLayer: 'translateX(20%)',
    scale: 'scale(0.7)',
    zIndex: 5,
    data: {
      src: 'https://i.pinimg.com/564x/64/6e/17/646e179ffb9aaaff4c674626ee204c0a.jpg',
      alt: 'Makima points her fingers in a gun-shaped hand gesture.',
    },
  },
  {
    moveFromTopLayer: 'translateX(50%)',
    moveToTopLayer: 'translateX(20%)',
    scale: 'scale(0.6)',
    zIndex: 4,
    data: {
      src: 'https://i.pinimg.com/564x/75/e4/d2/75e4d2c8868322d92e6254fe52929c34.jpg',
      alt: 'Denji transformed into the chainsaw man.',
    },
  },
];

export { moveAroundTopLayer };
