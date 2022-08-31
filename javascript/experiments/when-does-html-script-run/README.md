# When does HTML script run?

## Regular script tags with src

Load in the declared order.

## Scripts with async tag

### The loading order

Quote from MDN:

> For classic scripts, if the async attribute is present, then the classic script will be fetched in parallel to parsing and evaluated as soon as it is available.
>
> -- https://developer.mozilla.org/en-US/docs/Web/HTML/Element/script
> I had to increase the size from the first script. A larger size indicates longer loading time and delayed execution.

I had to clear the cache before loading a web page to verify that the execution order was correct.

The first script had to be large enough to be fetched after the second.

### Async script using variable from the other file

The script second.js get loaded before the first.js. In the second.js I referenced the variable from the first.js.

The variable is declared and initialized in the first.js.

Because the two scripts are fetched and executed in parallel, we may get an error.

If the first.js is loaded first, no error will happen.
