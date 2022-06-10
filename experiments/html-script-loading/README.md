# When does the HTML script load?

## Regular script tags with src

Load in the declared order.

## Scripts with async tag

Quote from MDN:

> For classic scripts, if the async attribute is present, then the classic script will be fetched in parallel to parsing and evaluated as soon as it is available.
>
> -- https://developer.mozilla.org/en-US/docs/Web/HTML/Element/script

I had to increase the size from the first script. Larger size indicates longer loading time and delayed execution.

I had to clear cache before loading a web page to verify that the execution order was correct.

The first script had to be large enough to be fetched after the second.
