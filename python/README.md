# Python

## Windows setup

To start working with the python code run:

1. Open command prompt and make sure you are in `python` directory.

   Your current location should be `sk-experiments/python`.

2. Check your python version

   ```cmd
   python --version
   ```

   Your python version should be the **Python 3.10.4**. That is the version I used when I created requirements.txt.

   _I am not sure should how do the python versions work and should they match._

3. Instantiate the virtual environment:

   ```cmd
   python -m venv env
   ```

   **Check do you have `env` directory. If you do, proceed. Otherwise you did something wrong.**

4. Run the python from the virtual environment

   ```cmd
   env\Scripts\activate.bat
   ```

5. Install the packages from the **requirements.txt**.

   ```cmd
   python -m pip install -r requirements.txt
   ```

6. Run the code

   ```cmd
   python main.py
   ```

## Formatting

1. Make sure you are in virtual environment.

   You should see _(env) C:\Users\<username>\..._.

2. Activate the virtual environment.
3. Run the format command.

   ```cmd
   black .
   ```

4. If the format command doesn't work, run:

   ```cmd
   python -m black .
   ```
