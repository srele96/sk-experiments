require('./a');
require('./b');

function getFilename(module) {
  return module.filename.replace(`${__dirname}\\`, '');
}

const app = getFilename(module);
const a = getFilename(module.children[0]);
const c = getFilename(module.children[0].children[0]);
const b = getFilename(module.children[1]);
console.log('-' + app);
console.log('  -' + a);
console.log('    -' + c);
console.log('  -' + b);
