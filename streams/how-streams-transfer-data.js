const { createWriteStream, createReadStream } = require('fs');
const { Readable } = require('stream');
const { join } = require('path');

// push alphabet characters to readable stream
const rs = new Readable({
  read: (function () {
    let alphabetChar = 97;

    return function () {
      // terminate after last character
      if (alphabetChar > 'z'.charCodeAt(0)) rs.push(null);
      else rs.push(String.fromCharCode(alphabetChar));
      alphabetChar += 1;
    };
  })(),
});

function getPath(fileName) {
  if (typeof fileName !== 'string') {
    throw new Error(fileName + 'is not a string');
  }
  return join(__dirname, 'out', fileName);
}

rs.pipe(createWriteStream(getPath('output.txt')));

// Create CPP file and build executable.
// Transfer executable using streams.
// Execute the transferred executable.
//
// If the copied executable is successfully executed, then
// the stream has successfully transferred the executable.
const source = createReadStream('./main.exe');
source.pipe(createWriteStream(getPath('main-copy.exe')));
// make executable content readable
source.pipe(createWriteStream(getPath('main-copy.txt')));
