const strictEqual = require('assert').strictEqual;
const { Readable, Writable } = require('stream');

// Readable stream reads data from somewhere.
// In this case reads data from `count` variable,
// then pushes the data in its internal buffer.
// When the reading is done, pushes null to officially
// finish reading.
let count = 5;
// When does the read() method run?
// Time before initialization.
console.log('before rs initialization');
const rs = new Readable({
  read() {
    if (count >= 0) {
      let s = `${count}`;
      this.push(s);
      console.log('push', s);
      count -= 1;
    } else {
      this.push(null);
    }
  },
});
// Is the read method already executed?
console.log('after rs initialization');
// No, read was not run here.

// Writable stream writes the data and calls next.
// Writable stream does not have to do anything,
// but must call next() to allow the flow to continue.
// It makes no sense to receive chunk and encoding
// and ignore them.
const ws = new Writable({
  write(chunk, encoding, next) {
    console.log('write', chunk.toString());
    next();
  },
});

ws.on('pipe', (src) => {
  console.log('something piped into writer');
  strictEqual(src, rs, 'received reader is same as the .pipe caller');
});

ws.on('unpipe', (src) => {
  console.log('something un-piped from writer');
  strictEqual(src, rs, 'received reader is same as the .pipe caller');
});

// teeing - in nodejs
// answer and explanation:
// https://stackoverflow.com/questions/17957525/multiple-consumption-of-single-stream
// one readable - multiple writable streams
// https://developer.mozilla.org/en-US/docs/Web/API/Streams_API/Concepts#teeing
rs.pipe(ws);
rs.pipe(ws);
