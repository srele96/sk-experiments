# Calculator demo

An app that demonstrates building packages using JavaScript and monorepo.

## Split logic using monorepo

Use module bundler to create a package that depends on another package which isn't published to NPM.

## Specs

For the sake of brevity let's make a calculator.

We will build a calculator app that has four operations:

```txt
+    add
-    subtract
*    multiply
/    divide
```

We are building a calculator. We split logic to the four packages.

Our calculator will use four packages. We use webpack to build our calculator package.
