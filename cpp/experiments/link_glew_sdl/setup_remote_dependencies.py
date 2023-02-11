#!/usr/bin/env python3

"""
setup remote dependencies robustly and print detailed error messages if any of the steps fail
create destination for the remote repository so the remote repository is cloned to the root of this project
overwrite the destination for the remote repository if it already exist and clone the remote repository
copy the contents of the directory libraries/ from remote repository to the root of this project
clean up the cloned repository
"""

import sys
import os
import shutil
import subprocess
import signal


def create_destination():
    # Make sure the destination always leads to the root of this project from
    # whichever destination the script is run from.
    script_path = os.path.dirname(os.path.abspath(__file__))
    destination = "dependencies"
    destination_path = os.path.join(script_path, destination)
    return destination_path


class Choice:
    def __init__(self):
        self.confirm = ["yes", "y"]
        self.deny = ["no", "n"]
        first = 0
        self.printable = [self.confirm[first], self.deny[first]]


def get_user_confirmation():
    while True:
        choice = Choice()
        # https://stackoverflow.com/questions/57052651/transforming-an-array-to-a-serie-of-parameters-in-python
        user_choice = input(
            "Do you want to overwrite the destination? [{}/{}] ".format(
                *choice.printable
            )
        )
        lowercase_user_choice = user_choice.lower()
        if lowercase_user_choice in choice.confirm:
            return True
        elif lowercase_user_choice in choice.deny:
            return False
        else:
            print("Invalid input. Please enter {} or {}.".format(*choice.printable))


def attempt_to_overwrite_destination(destination_path):
    if os.path.exists(destination_path):
        # https://stackoverflow.com/questions/28204936/python-format-best-practices
        print("The destination already exists. {0}".format(destination_path))
        should_overwrite = get_user_confirmation()
        if should_overwrite:
            # https://stackoverflow.com/questions/2656322/shutil-rmtree-fails-on-windows-with-access-is-denied
            shutil.rmtree(destination_path)
        else:
            # I wanted to use os.EX_OK but it throws error that module os does not have attribute EX_OK
            # https://stackoverflow.com/questions/6413831/exit-code-standards-in-python
            sys.exit(0)


def clone_remote_repository(destination_path):
    repository_url = "https://github.com/srele96/rtall.git"
    result = subprocess.run(
        ["git", "clone", repository_url, destination_path], capture_output=True
    )


def setup_remote_dependencies_robustly():
    """
    Setup remote dependencies robustly, so in case the script fails for
    whatever reason, user may attempt to rerun it and one of the subsequent
    reruns should succeed if everything is alright.
    """
    destination_path = create_destination()
    attempt_to_overwrite_destination(destination_path)
    clone_remote_repository(destination_path)


# CTRL+C caused the script to throw an exception KeyboardInterrupt so I added
# the basic signal handling to terminate the script.
# https://stackoverflow.com/questions/37887624/python-3-keyboardinterrupt-error
# https://stackoverflow.com/questions/1112343/how-do-i-capture-sigint-in-python
def terminate_process(*args):
    # Add newline because termination isn't followed by enter.
    print("\nCaught CTRL+C. Exiting...")
    sys.exit(1)


signal.signal(signal.SIGINT, terminate_process)


if __name__ == "__main__":
    setup_remote_dependencies_robustly()
