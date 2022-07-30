# new

Create new experiment directory consistently from one template.

## Docs

```
new <directory>                       Creates directory with empty package.json description.
new <directory> -d, --description     Creates directory with provided description for package.json.
```

## Usage

Create a new directory with description:

```
new my-awesome-experiment -d "my awesome description"
```

Create a new directory with empty description:

```
new my-awesome-experiment
```

Create a new directory with one-word description:

```
new my-awesome-experiment -d description
```

Create nested directory:

```
new my-dir
new my-dir/nested
new my-dir/nested/also-nested
```

Error, directory already exists:

```
new mydir
new mydir
```
