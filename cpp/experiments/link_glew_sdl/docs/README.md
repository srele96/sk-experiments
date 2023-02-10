# Documentation

## Create python virtual environment

My Python version at the time of writing is `3.10.4`. To check python version run:

```cmd
python --version
```

1. Make sure you are in the root directory of this project.
2. Run `pythom -m venv env` to create directory `env` which will contain python virtual environment.
3. Run `env\scripts\activate` to activate the virtual environment in the terminal.
4. You should see something like: `(env) C:\<path-to-project>\`

## Install python packages

1. Follow steps to create virtual environment.
2. Run `env\scripts\activate` to activate the virtual environment in the terminal.
3. Make sure you are in the directory with `requirements.txt` file.
4. Run `pip install -r requirements.txt` to install python packages.

## Format python code

1. Follow steps to create virtual environment.
2. Run `env\scripts\activate` to activate the virtual environment in the terminal.
3. Run `black .` to format python code.

## Exit python virtual environment

[StackOverflow - How to exit python virtual environment](https://stackoverflow.com/questions/990754/how-to-leave-exit-deactivate-a-python-virtualenv)
