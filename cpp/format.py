#!/usr/bin/env python3

import sys
import subprocess
import os

class Formatter:
    def __init__(self):
        self.extensions = ['.cpp', '.h', '.hpp']
        self.files = []
        self.save_files_with_extensions()

    def save_files_with_extensions(self):
        for root, _, filenames in os.walk('.'):
            for filename in filenames:
                has_valid_extension = os.path.splitext(filename)[1] in self.extensions
                # The file is always a child of all the directories in the
                # path, so if any of the parent directories are 'build',
                # we can ignore the file.
                not_ignored = 'build' not in root.split(os.sep)

                if has_valid_extension and not_ignored:
                    self.files.append(os.path.join(root, filename))

    def check(self):
        print('Searching for unformatted files...')
        for file in self.files:
            # Use --output-replacements-xml to get a list of replacements that
            # clang-format would make. If there are any, the file is not
            # formatted.
            result = subprocess.run(
              ['clang-format', '--output-replacements-xml','-style=file', file],
              stdout=subprocess.PIPE,
              stderr=subprocess.PIPE
            )
            output = result.stdout.decode('utf-8')

            not_formatted = '<replacement ' in output
            if not_formatted:
                print('File is not formatted', file)
                exit(1)
        print('All files are formatted.')

    def format(self):
        for file in self.files:
            print('Formatting file: ' + file)
            subprocess.run(['clang-format', '-i', '-style=file', file])

def run_formatter():
    formatter = Formatter()
    if '--check' in sys.argv:
        formatter.check()
    else:
        formatter.format()

if __name__ == '__main__':
    run_formatter()
