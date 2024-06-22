const world = require('../../hello/world');

module.exports = function mod() {
  return 'tenant one mod function\n' + world();
};
