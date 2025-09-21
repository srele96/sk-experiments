#!/bin/bash

################################################################################
# Competitive Programming compilation script for Linux
# Inspired by CSES Book: https://cses.fi/book/book.pdf
################################################################################

linebreak="----------------"
echo "$linebreak"

outDir="build"

# Create build directory if it doesn't exist
if [ ! -d "$outDir" ]; then
  echo "Creating $outDir directory"
  mkdir -p "$outDir"
  echo "$linebreak"
fi

filename=$1

if [ -n "$filename" ]; then
  file="$filename.cpp"
  out="$outDir/$filename"

  echo "Compiling $file to $out"
  g++ -std=c++20 -O2 -Wall "$file" -o "$out"

  if [ $? -eq 0 ]; then
    echo "Done."
    echo "$linebreak"
    echo "Running $out"
    echo ""
    "$out"
  else
    echo "Compilation failed."
  fi
else
  echo "No filename provided."
  echo "$linebreak"
  exit 1
fi
