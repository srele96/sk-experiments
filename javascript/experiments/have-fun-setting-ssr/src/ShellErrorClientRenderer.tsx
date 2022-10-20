function ShellErrorClientRenderer() {
  return (
    <html>
      <head>
        <title>Client Renderer</title>
      </head>
      <body>
        <div id="__root">
          <p>Loading...</p>
        </div>

        <script src="clientrenderer.js" />
      </body>
    </html>
  );
}

export { ShellErrorClientRenderer };
