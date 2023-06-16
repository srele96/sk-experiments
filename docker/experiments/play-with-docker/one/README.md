# One

Service one.

## Docs

Build image:

```powershell
docker build -t one:latest .
```

List images:

```powershell
docker images ls
```

Run image:

```powershell
docker run --rm -it -p 4000:4000 one:latest
```
