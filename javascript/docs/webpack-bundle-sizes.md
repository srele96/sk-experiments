# Webpack bundle sizes

In very simplified terms, bundle size is the number of characters. We can reduce
the bundle size by code-splitting and other techniques. Minimizing code renames
variables to one character. However, there are more optimization methods, but I
won't cover them here. Caching comes in different forms. Browsers cache files,
so Webpack adds hashes in chunk names. Chunk is a fancy term for a file, so how
do we calculate size? We can calculate chunk size by the number of characters.
A character weighs 8 bits. If we have a bundle of 1MB, that is 8000 bits,
meaning 1000 characters.
