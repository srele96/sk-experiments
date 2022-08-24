# I tried to chain pipes, but I needed to use teeing.

I wanted to create two copies of a file. My implementation created two read streams, but I wanted to use one. Because a read stream can be read once, I thought I should chain pipes. However, I was wrong. I tried to use the transformation technique, but I needed teeing. So, how did I figure it out?

## Resources

- [Docs NodeJS - Buffer](https://nodejs.org/api/buffer.html) - Streams use an internal buffer
- [Docs NodeJS - Streams](https://nodejs.org/api/stream.html) - All relevant information about NodeJS streams
- [Understanding Streams in NodeJS](https://nodesource.com/blog/understanding-streams-in-nodejs/) - Blog post
- [NodeJS Streams Pipe and Chaining](https://www.naeemrana.com/node-js/node-js-streams-pipe-and-chaining/) - Blog post

## How did I figure out how streams work?

I've read implementation of `createReadStream` and `createWriteStream`.

I went to [NodeJS core modules implementation](https://github.com/nodejs/node/tree/d96a2ea615b4090bb8cd53a9bc7fcba231479e12/lib) and looked for the `createWriteStream` implementation. I needed to understand how experienced developers use streams.

I've read the following implementations:

- [createWriteStream](https://github.com/nodejs/node/blob/d96a2ea615b4090bb8cd53a9bc7fcba231479e12/lib/internal/fs/promises.js) - Used by me.
- [WriteStream](https://github.com/nodejs/node/blob/d96a2ea615b4090bb8cd53a9bc7fcba231479e12/lib/internal/fs/streams.js) - Used by `createWriteStream`.
- [fs.write](https://github.com/nodejs/node/blob/d96a2ea615b4090bb8cd53a9bc7fcba231479e12/lib/fs.js) - Used by `WriteStream`.

I concluded that the source of data flow goes something like this:

1. Start reading the resource from the desired destination
2. Write the read resources into the `Readable` stream
3. Pump the data from the `Readable` stream to the `Writable` stream
4. Write the data received by the `Writable` stream to the desired destination

Reading the `createWriteStream` and `createReadStream` helped me understand how they work together. The `Reader` uses the `fs` module that reads chunks of data from a file. Then they get written to the `Reader`'s internal buffer. Piping the `Reader` to a `Writer` makes the reader pump data to the `Writer`. Lastly, the `Writer` writes data to a destination.

From my current understanding, streams are data transfer mediums.

```js
/* resource -> ReadableStream -> WritableStream -> destination */
```

Although, we can do it another way.

```js
/* resource -> ReadableStream -> /code that reads stream untill empty/ */
```

Or another way:

```js
/* /code that pumps the data to a stream/ -> WritableStream -> destination */
```

## From failing to understand to finding an answer

I wanted to read a file and write it to two locations. I thought I should use [pipe chains](https://developer.mozilla.org/en-US/docs/Web/API/Streams_API/Concepts#pipe_chains). A few hours of reading later, I figured it out. My solution doesn't conceptually fit. I was supposed to `tee`, but I tried to `pipe chain`. I believe I could implement `teeing` by `chaining pipes`. However, that would make it unnecessarily complicated. I drew the following conclusions:

- What do I want to make (define requirements well and as specific as possible)?
- Find a concept that solves my problem.

I realized I didn't know what I was doing, so I started to read concepts. In the teeing section, I recognized my requirements. I searched how to tee streams in NodeJS and found a solution.

Before:

```js
const { createWriteStream, createReadStream } = require('fs');
const join = require('path').join;

// not teeing
createReadStream('./main.exe').pipe(
  createWriteStream(join(__dirname, 'out', 'main-copy.exe'))
);
createReadStream('./main.exe').pipe(
  createWriteStream(join(__dirname, 'out', 'main-copy.txt'))
);
```

After:

```js
const { createWriteStream, createReadStream } = require('fs');
const join = require('path').join;

const source = createReadStream('./main.exe');
// teeing
source.pipe(createWriteStream(join(__dirname, 'out', 'main-copy.exe')));
source.pipe(createWriteStream(join(__dirname, 'out', 'main-copy.txt')));
```

I didn't want to have two read streams. To achieve that, I should probably pipe them, like:

```js
createReadStream('./main.exe')
  .pipe(createWriteStream(join(__dirname, 'out', 'main-copy.exe')))
  .pipe(createWriteStream(join(__dirname, 'out', 'main-copy.txt')));
```

After I tried to chain pipes, I got an error. Not knowing what the error meant, I started reading documentation. After a while, I realized a stream pipe returns a stream. It gave me a writable stream instead of a readable one, and I didn't know why. I wasn't using the concept correctly.

An error made me think until I figured it out. If a pipe doesn't exist on a writable stream, I must return a readable stream. Pipe returns stream passed as input or whatever. Then I can read from the readable stream and write to another destination. I started to figure out piping, reading, writing, etc. But I was wrong again. I still don't fully understand chaining. I didn't want to transform my data, but I used the concept for it.

## I didn't need to chain pipe calls

Pipe chains are used for data transformation. I could move data by chained pipes, but it doesn't feel right. They do something like this:

1. Read
2. Transform
3. Write

Pipe chaining and teeing together.

```js
// read
const readable = getReadableStreamSomehow();
const transform = getTransformStreamSomehow();
// transform
const transformed = readable.pipe(transform);
// tee and write
transformed.pipe(writeStreamTo('a.txt'));
transformed.pipe(writeStreamTo('b.txt'));
```

## Answer to my questions

My question:

```js
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
```

An answer:

```js
// Code taken from fs - node core module:
// https://github.com/nodejs/node/blob/d96a2ea615b4090bb8cd53a9bc7fcba231479e12/lib/internal/fs/streams.js
// Writer writes received data to desired destination. In this case, to a file.
WriteStream.prototype._write = function (data, encoding, cb) {
  this[kIsPerformingIO] = true;
  this[kFs].write(this.fd, data, 0, data.length, this.pos, (er, bytes) => {
    this[kIsPerformingIO] = false;
    if (this.destroyed) {
      // Tell ._destroy() that it's safe to close the fd now.
      cb(er);
      return this.emit(kIoDone, er);
    }

    if (er) {
      return cb(er);
    }

    this.bytesWritten += bytes;
    cb();
  });

  if (this.pos !== undefined) this.pos += data.length;
};
```
