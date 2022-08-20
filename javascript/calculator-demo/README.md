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

## Initiate repository

Run _(The following command is a shorthand for `yarn install`)_:

```terminal
yarn
```

## Build package

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

## Outcome

Using yarn workspaces every package will be installed in the root `node_modules`
directory. That allows multiple teams to work on each individual package. Or
one team to work on each package. It is easier to migrate from monorepo to
multirepo than the other way around. Look this up on the internet, don't take
my word for it.

Using webpack the entry point is a calculator. It will look up the code
calculator is using and produce a build.

We test build afterwards. The build is UMD module which means we can use it in
the browser and NodeJS environments. Look up on the internet about packages for
NodeJS and Browsers. They require
[shimming](https://developer.mozilla.org/en-US/docs/Glossary/Shim).

We test named and default exports in NodeJS, by printing results. In the browser
we do the same.

Declaring a directory as workspace directory:

```json
{
  "name": "calculator-demo",
  "version": "0.1.0",
  "workspaces": ["packages/*"]
}
```

The key here is `workspaces` property. Declares all directories in `packages`
as workspace. Each of them needs to have package.json.
