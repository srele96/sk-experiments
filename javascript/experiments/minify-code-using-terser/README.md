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
- Compare minified code with the original.
- Format minified code to see differences.
- Run minified code and verify it runs.

## Details

- Install terser and run it on a small code sample to see what happens.
- Create a larger code sample to check the terser's behavior.
- Minify code using three different flags to verify different behaviors.
- Use scripts in package JSON to simplify:
  - Minification process.
  - Verification that minified code runs.
- Create a minified file for each mode to compare them simultaneously.
- Commit minified code to see the difference on GitHub. Minified code is small so it is fine. Usually, build output isn't committed to version control.
