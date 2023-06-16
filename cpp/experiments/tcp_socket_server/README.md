# C++ TCP/IPv4 Socket Server

Create a TCP/IPv4 Socket Server using C++.

## Articles I've read

- [Getting Started with Winsock](https://learn.microsoft.com/en-us/windows/win32/winsock/getting-started-with-winsock)
- [Winsock2 header overview](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/)

It took me around eighteen hours to go through the good part of the documentation. I also read through some details of HTTP RFC - Hyper-Text Transfer Protocol Request For Comments standard.

## It took me a while to figure out how to write an HTTP response to a socket

From using C++ and documentation for socket programming on Microsoft documentation to an HTML page, An HTTP response is just plain text. Once I had the code that could accept a client socket so I could write to it, I had a problem. I managed to write a string like this "hello":

```txt
response = "hello"
```

But After that, I wondered why the browser doesn't show it as an HTML. I realized that is because the browser needs to know the content type of my response. That would mean I need to add an HTTP header to my response from the server. Therefore I tried to do it like this:

```txt
response = "Content-Type: text/html" + "HELLO"
```

I did not see a problem with this response. So I fired up a browser, went to localhost, and the response, to my surprise, was this:

```txt
"Content-Type: text/htmlHELLO"
```

So I needed to add a space between the two.

```txt
"Content-Type: text/html HELLO"
```

That did not work. Alright, since the HTTP response is plain text, how do format it to work? Read an [RFC for HTTP](https://www.rfc-editor.org/rfc/rfc7231#page-73), I thought!
They tell me to do the same thing I'm doing. But unfortunately, the RFC only shows part of an HTTP response. I was sure I put together the response well, but something was missing.

Since the RFC did not answer, I decided to google it up - "write HTTP header socket." And it turns out I was close. [This StackOverflow answer](https://stackoverflow.com/questions/8315209/sending-http-headers-with-python) popped up, it showed an HTTP response using python, and it resembled what I was trying to do. The code for the HTTP response on StackOverflow started like this:

```txt
"HTTP/1.0 200 OK\r\n"
```

Damn, that's what I was missing. But the StackOverflow answer code uses version 1.0, and I am using 1.1 according to what my server was logging. So why does each line have escaped characters at the end?

At a glimpse, I noticed a comment saying this:

> "... and don't forget to replace \n\n to \r\n\r\n, since HTTP needs CRLF after headers."

So that was it; I needed those escaped characters. But there is one more thing, why duplicate escaped characters? He used formats like:

```txt
"HTTP/1.1 200 OK/r/n"
"Content-Type: text/html\r\n\r\n"
"<html><body><h1>Response</h1></body></html>"
```

Why is it like that? So I tried to add another header:

```txt
"HTTP/1.1 200 OK/r/n"
"Content-Type: text/html\r\n\r\n"
"Access-Control-Allow-Origin: *\r\n\r\n"
"<html><body><h1>Response</h1></body></html>"
```

That does not work. Why? That is because we need one fully separated space between the response body and headers. So the format of the HTTP response (according to my current understanding, which may be wrong) is as follows:

```txt
PROTOCOL/VERSION RESPONSE_CODE RESPONSE_STATUS
HEADER
HEADER
HEADER

BODY
```

Or in other words:

```txt
HTTP/1.1 200 OK
Content-Type: text/html
Access-Control-Allow-Origin: *

<!DOCTYPE html>
<html>
  <head>
    <title>HTTP Response</title>
  </head>
  <body>
    <h1>HTTP Response</h1>
  </body>
</html>
```

And that worked! That looks like quite a lot of work is required to implement a server using plain sockets and C++. That is where some library hops in and reduces the work we need to do.

I had a lot of fun researching HTTP and sockets in C++!
