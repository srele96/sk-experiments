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

## Build package

Development

```terminal
yarn build:prod
```

Production

```terminal
yarn build:dev
```

Development and production

```terminal
yarn build
```

## Run tests

First build the package.

To test in browser:

1. Go to `__tests__` directory
2. Open `useDevBuild.html` in browser
3. Open `useProdBuild.html` in browser
4. Open the developer console and verify that output is there

To test in nodejs run:

```terminal
yarn test
```

## References

- Read about [Yarn workspaces](https://yarnpkg.com/features/workspaces).
