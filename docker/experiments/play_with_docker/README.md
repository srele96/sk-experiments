# Play with docker

Services are named poorly `one` and `two` because i was trying to be _"fast"_ which I wasn't. Well, that's subjective whether I was fast or not.

I had the help of all the AI bots of the world, ChatGPT and GitHub copilot and my own brain which I train trying various things. This was one of them.

Create services and turn them into containers using docker and docker compose.

Ignore all good practices for the sake of practicing and playing around with docker configuration.

## Architecture

![Architecture](./architecture.png)

### Architectural decisions

All architectural decisions were made for fun and to make my life even more complicated than it currently is.

My goal was to cause myself as many problems are possible to have as many things to fix to learn as much as possible.

## How to use

```powershell
docker compose up --build
```

Services on the port `4000`:

```txt
http://localhost:4000/
http://localhost:4000/foo
http://localhost:4000/bar
```

Services on the port `3000`:

```txt
http://localhost:3000/
http://localhost:3000/foo
http://localhost:3000/bar
http://localhost:3000/postgres
```

## Documentation

Initially:

```powershell
docker compose up
```

If you make changes to docker files or code:

```powershell
docker compose up --build
```
