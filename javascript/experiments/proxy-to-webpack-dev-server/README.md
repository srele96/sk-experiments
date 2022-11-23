# Using Proxy setup ReactJS, Webpack Dev Server, Fast Refresh, NodeJS express, and a template engine

I will use a proxy for the working setup of ReactJS with Webpack Dev Server, Fast Refresh, NodeJS Express, and a Template Engine.

## What if I have a traditional server and want to add the part of the page to be in react?

ReactJS is the code that runs on the client. On top of it, we want to use JSX. That's a bummer because we have to use some tool to compile that javascript. Then we need to integrate that with a fast refresh! The problem is getting bigger; here is my idea of how to solve it.

Create a separate directory for that part of the application. We will place Webpack and other configuration files in that directory. Now we can compile files using Webpack. How do we use a fast refresh, a Webpack development server, and a regular express server with a template engine? We could run the Webpack development server, but where is the page with links to javascript files? An express server is hosting that page, and the Webpack development server doesn't know about it. How can we integrate the Webpack and regular server?

## We can split the roles

The Webpack development server provides hot module reloading, paths to javascript files, and serves the compiled content.

The express server will handle all front-line requests. For any requests it can't take, like the compiled files, our express server can proxy to our Webpack development server. That way, the Webpack development server provides almost everything we want out of the box, and we have almost everything we need.

How does that even work? Let's imagine what the first thing we do when we want to open youtube is.

- Open a web browser
- Enter the path like [https://www.youtube.com](https://www.youtube.com)
- The server on [https://www.youtube.com](https://www.youtube.com) sends an HTML response to the browser.
- The browser parses the HTML response and sends back requests to the server whenever it finds a link, script, or other tags with a relative path.
- The server receives that request and tries to send a response.
- Our server won't know about compiled javascript files, so it asks the Webpack development server for them.
- The Webpack development server knows about those files and sends back their content.

What about hot module reloading? How does that even work? It is implemented using web sockets and works similarly to the previous example. They also depend on the paths on the web. We have to proxy the WebSocket stuff from our express server to the Webpack development server.

Why do we have to do it like this? The Webpack development server could be better at setting up other tools. However, proxying does the job well, and we can put less effort into setting it up differently with other stuff.

So, what was our initial problem? We wanted to use fast refresh on the part of our page. We want to use the express server and serve a part of our page using the Webpack development server.

## Why does all of that work?
