const { createWriteStream, createReadStream } = require('fs');
const { Readable } = require('stream');
const { join } = require('path');

// Ideally read function has its own scope, here I used closure to achieve that.
const rs = new Readable({
  read: (function () {
    let alphabetChar = 97;

    return function () {
      if (alphabetChar > 'z'.charCodeAt(0)) rs.push(null);
      else rs.push(String.fromCharCode(alphabetChar));
      alphabetChar += 1;
    };
  })(),
});

// Or alternatively...
//
// let alphabetChar = 97;
// const rs = new Readable();
// rs._read = function () {
//   if (alphabetChar > 'z'.charCodeAt(0)) rs.push(null);
//   else rs.push(String.fromCharCode(alphabetChar));
//   alphabetChar += 1;
// };

// Or alternatively...
// let alphabetChar = 97;
// const rs = new Readable({
//   read: function () {
//     if (alphabetChar > 'z'.charCodeAt(0)) rs.push(null);
//     else rs.push(String.fromCharCode(alphabetChar));
//     alphabetChar += 1;
//   },
// });

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
// What does this example achieve and prove?
// - Streams can transfer any kind of data (.exe, .txt, .zip, etc...)
// - Computers transfer data using streams
// - Streams don't care about the type of data they work with.
// - Humans make data type differentiation, but for computers all
//   of it is 0 and 1
//
// Last step
//
// If the copied executable is successfully executed, then
// the stream has successfully transferred the executable.
const source = createReadStream('./main.exe');
// streaming one source to two destinations is called teeing
source.pipe(createWriteStream(getPath('main-copy.exe')));
// make executable content readable
source.pipe(createWriteStream(getPath('main-copy.txt')));
