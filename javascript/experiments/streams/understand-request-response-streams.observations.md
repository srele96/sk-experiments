# Request and Response Stream - Observations

## Chunk collecting

The listener receives data in chunks. Because the server receives data in chunks, the data is split.

```js
req.on('data', function saveChunkDataAndChunkCount(chunk) {
  body += chunk;
  chunksReceived += 1;
});
```

How large can each chunk be?

## Analysis:

I opened postman and started sending get requests. I added more characters to each request. I printed each chunk and incremented chunk counter. I observed that it took 50kb or more to increase chunk count. I started sending requests with more characters. I observed that request with 88 chunks took 'a while'.

```js
const chunkStatistic = JSON.stringify({
  chunkCount: chunksReceived,
  received: body,
});
```

## All previous observations draw the following conclusions

- `Request` and `Response` are streams.
- `Request` is a readable stream.
- `Response` is a writable stream.

Reading and writing to Request and Response streams is kind of hidden from the user. But there is possibility to manually fetch and write data to streams. Manual control of reading and writing allows us to control the fetch priority.

## References

- [NextJS - Streaming SSR](https://nextjs.org/docs/advanced-features/react-18/streaming#using-streaming-server-rendering)

_I wanted to add a link to the document by Dan Abramov about the streaming SSR, but I couldn't find it. Still, I wanted to note that it exists._
