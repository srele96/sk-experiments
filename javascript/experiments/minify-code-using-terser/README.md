# Minify code using terser

See minified terser output out of curiosity.

## Terser GitHub

See [terser on GitHub](https://github.com/terser/terser).

## Implement

- Install terser.
- Create sample code to minify.
- Minify code using:
  - Default flag.
  - Mangle flag.
  - Compress flag.
- Compare minified code with original.
- Format minified code to clearly see differences.
- Run minified code and verify it runs.

## Details

- Install terser and run it on small code sample to see what happens.
- Create larger code sample to check terser's behavior.
- Minify code using three different flags to verify different behaviors.
- Use scripts in package json to simplify:
  - Minification process.
  - Verification that minified code runs.
- Created minified file for each mode to compare them simultaneously.
- Commit minified code to see difference on github. Minified code is small so it is fine. Usually build output isn't commited to version control.
