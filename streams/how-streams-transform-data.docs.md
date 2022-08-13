# How streams transform data

An attempt to use transform streams.

## Requirements

Input goes from 5 to 1 (both included).

```js
// Input sequence:
// 5
// 4
// 3
//
// Output sequence:
// { transformedChunk: 1, data: 5 }
// { transformedChunk: 2, data: 4 }
// { transformedChunk: 3, data: 3 }
```

## Thoughts

This transformation is probably incorrect. If received numbers
were from a file, the whole output would be mutated.

I wanted to count received chunks and return them to the client. I guess I used
the wrong method to implement that requirement. A good transform stream usage
is encryption or decryption, compression, and more.
