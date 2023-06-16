# Render React on the Server

The mock setup to render React on the server.

## Goals

I wanted to render `react` on the server using `@babel/register` for fun.

Six months ago this topic was very mystical to me.

Reading various topics has improved my learning speed.

It was quite fun to set up this sample.

## The problem

A year ago I learned about Single Page Application challenge for Server Side rendering.

I tried to learn the tooling like:

- Babel
- Webpack
- Terser
- All that good stuff...

I couldn't manage it. It felt like it was too much.

Turns out, I was lacking learning methodology.

The problem this sample solves is:

Quick and dirty setup of Server Side Rendering for Reactjs.

It is quick and dirty because babel documentation doesn't recommend `@babel/register`.

Another reason is I should know how babel, its presets and options work together.

I can assemble a running code. However, a running code doesn't mean it's working code.

## The solution

Use `@babel/register` to compile `react` components and jsx.

I wanted to use JSX syntax to render `react` components on the server.

Create `Chrome` component to wrap the page. I saw that react team has such in their fixtures directory.

Oh... shoot! I could've set up the client side rendering using `react-scripts`!

Oh well... too late now.

I lost my interest.

I played enough with this code sample.
