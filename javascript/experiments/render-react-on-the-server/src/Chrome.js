function Chrome(props) {
  return (
    <>
      <html lang="en">
        <head>
          <meta
            name="viewport"
            content="width=device-width, initial-scale=1.0"
          />
          <title>{props.title}</title>
        </head>
        <body>
          {props.children}
          {/*
           ** React has XSS prevention mechanism.
           ** Don't do this.
           ** I wanted to try it out.
           **/}
          <script
            dangerouslySetInnerHTML={{
              __html: 'console.log("Please run me on the client!");',
            }}
          />
        </body>
      </html>
    </>
  );
}

export { Chrome };
