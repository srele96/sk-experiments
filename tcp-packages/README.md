# TCP packages

Using UNIX [tcpdump](https://www.tcpdump.org/index.html#documentation) on
[wsl](https://docs.microsoft.com/en-us/windows/wsl/install), this sample
code features a way to monitor TCP traffic on a port.

## Important notes

- Doesn't work on Windows. If you are using Windows, you need WSL.
- Run everything from WSL, otherwise won't work.

## What units does this sample have?

- Server on http://localhost:3000
- Server that serves client that sends request to http://localhost:3000
- UNIX script that listens to TCP traffic on the port 3000

## How does it work?

1. Server on the address http://localhost:3000 is serving the data.
2. Another server serves the client that sends a get request to
   http://localhost:3000.
3. A UNIX script catches the received traffic on port 3000 and logs it to the
   console.

## Logical units

1. `serve-data.js`
2. `serve-client.js`
3. `sudo tcpdump -v -i any port 3005`

## How to run it

1. Start the server to serve data
2. Start the script to monitor TCP traffic
3. Start the server to serve client to send request

Alternatively, start all three at the same time. After that, refresh the client
and the traffic should be visible.

The script sample output:

```txt
12:08:14.028945 IP localhost.33255 > localhost.https: Flags [S], seq 1828376761, win 43690, options [mss 65495,sackOK,TS val 108010971 ecr 0,nop,wscale 7], length 0
12:08:14.028959 IP localhost.https > localhost.33255: Flags [R.], seq 0, ack 1828376762, win 0, length 0
```

## References

- [StackOverflow - Monitor TCP traffic on specific port](https://superuser.com/questions/604998/monitor-tcp-traffic-on-specific-port)
- [tcpdump](https://www.tcpdump.org/index.html#documentation) - Documentation
- [wsl](https://docs.microsoft.com/en-us/windows/wsl/install) - Windows Subsystem Linux
