# gitignore subdirectories

Does subdirectory gitignore override parent directory gitignore?

Yes, it does.

# Important notes

- I was in root directory while executing steps below.
- Root directory `.gitignore` was empty.

## How I tested it

Observation 1:

Adding file to gitignore after staging it, will not remove it from staging.

Steps I did to test this:

1. Create empty .gitignore
2. Create env file
3. Run `git add .`
4. env file will be staged
5. set gitignore to look like this `.gitignore` in this repository
6. Run `git status`
7. env file will be still staged

Steps that prove subdirectory gitignore overrides parent one:

1. Create empty .gitignore
2. Add files to be gitignored
3. Run `git add`
4. Run `git status`
5. Gitignored file in subdirectory wont be staged

## Why is this important?

This will allow me to have many subdirectories containing their own gitignore which is important to me because of `node_modules`.
