# Using Proxy setup ReactJS, Webpack Dev Server, Fast Refresh, NodeJS express, and a template engine

I will use a proxy for the working setup of ReactJS with Webpack Dev Server, Fast Refresh, NodeJS Express, and a Template Engine. The following text explains the problem and provides one solution, how, and why it works.

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

First, what is a browser? A browser is a program good at parsing text. It reads the text and tries to use it appropriately (in other words, it tries to parse it). So what else does it let me do? It allows me to browse the content of my computer. Why am I saying this? Because browsing the content of my computer is similar to visiting YouTube. The difference is that my computer allows the browser to open anything, and the YouTube server allows a browser to enter only parts of it.

If you have a Windows machine and open C drive through a browser, you are browsing a directory. For example, this link file:///C:/.

So, what is the code? The code is a text, and since the browser is good at parsing text, we can send it some code.

Then, let's think about what happens when we open a web page. What is a web page? A web page is a massive piece of text! Since I want to create a web server, whenever a browser goes to my address of http://localhost:3000, I will give it back some text, but I will tell it that the text is in the particular HTML format.

Frontend developers know what HTML is. Otherwise, look it up. If you have experience creating software, you will understand.

The browser is a good boy and will parse the text in the HTML format. When the browser parses the page, it starts reading through the content. It is going to send a web request for every link it sees. What does it tell us?

The script tag has a link. Then the browser will be like, hey, you sent me HTML, and there is a script tag with a uniform resource location. That script wants to run some code on that uniform resource location. Can you give it to me?

Our server is a good boy, it can not handle that address, but we are wise. So, we will forward it to the Webpack development server, and the Webpack development server is running and compiling files while sending the content for each request as a response. It is working hard with our configuration that we spent one hour putting together! Then it will give back the script content to our server. Our server is happy and sends JavaScript code to the browser which runs that code.

## So, how is it going to work again?

We want to have a page where react lives only on one part. That means we need an HTML element as the root. The page with root needs to know all the links to the compiled JavaScript with ReactJS code for that root. That is why we need to help the server out. We will get the paths to all files from [the manifest file that Webpack documentation mentions](https://webpack.js.org/concepts/manifest/). Why manifest? Because it's lightweight and small. Writing files on a computer is slow, no matter how fast it seems, so we want to write the absolute minimum.

The Webpack promises us that there are paths for javascript files that we need, so we will use that to get them. But first, write that file to the directory because the express doesn't know about compiled files. That is the only way it can get paths to get their paths, read from the manifest.

Alternatively, we can send them through an HTTP response to keep them in memory.

Our express server can read that file, create HTML script tags with the links from that file and insert the script tags to a page that needs the ReactJS code for the root we want to mount ReactJS on.

## Conclusion

There we go, we create a file with paths to JavaScript files, our server reads them, inserts them in the page, the browser parses the page, and asks for the content on those paths, our server can't find them, so it asks Webpack, and Webpack sends the content back, and our server gives the javascript back to the browser.
