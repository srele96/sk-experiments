# Create static content for web app using PowerShell

I wanted to have some fun using PowerShell doing some random ideas. The core idea was to create some files using PowerShell. I started playing around and doing the random ideas, then I realized I could create some html, javascript and css files using PowerShell. I wanted to check out if they work, so I created a server that serves the content from the directory.

## Documentation

First, create directory with content that the server will serve.

```cmd
.\create_content
```

Second, start the server to serve the content.

```cmd
.\start_server
```

Lastly, open the `http://localhost:3000` in your browser to see the content.
