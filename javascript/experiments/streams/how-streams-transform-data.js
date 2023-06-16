const { Readable, Transform, Writable } = require('stream');

const input = new Readable({
  read: (function () {
    let count = 5;
    return function () {
      if (count > 0) this.push(`${count}`);
      else this.push(null);
      count -= 1;
    };
  })(),
});

const transform = new Transform({
  transform: (function () {
    let transformedChunk = 0;
    return function (chunk, encoding, cb) {
      transformedChunk += 1;
      this.push(JSON.stringify({ transformedChunk, chunk: chunk.toString() }));
      cb();
    };
  })(),
});

const output = new Writable({
  write(chunk, encoding, cb) {
    console.log(chunk.toString());
    cb();
  },
});

input.pipe(transform).pipe(output);
