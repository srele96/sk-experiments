#!/usr/bin/env python3

import os
import subprocess

def collect_files():
    files = []
    for root, _, filenames in os.walk("."):
        for filename in filenames:
            if filename.endswith(".cpp"):
                files.append(os.path.join(root, filename))
    return files

def compile_files(files):
    compile = " ".join((
        "clang++",
        "-std=c++17",
        "-o",
        "main",
        " ".join(files)
    ))
    subprocess.run(compile, shell=True)

def run():
    print("Collecting files...")
    files = collect_files()
    print("Compiling...")
    compile_files(files)
    print("Running...")
    subprocess.run("./main")

if __name__ == "__main__":
    run()
