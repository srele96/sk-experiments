#!/usr/bin/env python3

import sys
import subprocess
import os

class Formatter:
    def __init__(self):
        self.extensions = ['.cpp', '.h', '.hpp']
        self.files = []
        self.find_files_with_extensions()

    def find_files_with_extensions(self):
        for root, _, filenames in os.walk('.'):
            for filename in filenames:
                has_valid_extension = os.path.splitext(filename)[1] in self.extensions
                not_ignored = 'build' not in root
                if has_valid_extension and not_ignored:
                    self.files.append(os.path.join(root, filename))

    def check_files(self):
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

    def format_files(self):
        for file in self.files:
            print('Formatting file: ' + file)
            os.system('clang-format -i -style=file ' + file)

def run_formatter():
    formatter = Formatter()
    if '--check' in sys.argv:
        formatter.check_files()
    else:
        formatter.format_files()

if __name__ == '__main__':
    run_formatter()