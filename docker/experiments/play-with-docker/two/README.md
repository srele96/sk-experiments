# Two

Service two.

## Docs

Build image:

```powershell
docker build -t two:latest .
```

List images:

```powershell
docker images ls
```

Run image:

```powershell
docker run --rm -it -p 4000:4000 two:latest
```
