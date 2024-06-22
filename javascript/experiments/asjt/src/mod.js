const world = require('./hello/world');
const ocean = require('./hello/ocean');

module.exports = function mod() {
  return 'default mod function\n' + world() + '\n' + ocean();
};
