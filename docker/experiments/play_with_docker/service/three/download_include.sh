#!/bin/bash

__dirname="$(cd "$(dirname "$0")" && pwd)"
include="include"
include_path="${__dirname}/${include}"

# if the directory include does not exist, create it
if [ ! -d "${include_path}" ]; then
  echo "Creating directory ${include_path}"
  mkdir "${include_path}"
else
  echo "Directory ${include_path} already exists."
fi

mongoose_h_url="https://raw.githubusercontent.com/cesanta/mongoose/7.9/mongoose.h"
mongoose_h="mongoose.h"
mongoose_h_path="${include_path}/${mongoose_h}"
mongoose_c_url="https://raw.githubusercontent.com/cesanta/mongoose/7.9/mongoose.c"
mongoose_c="mongoose.c"
mongoose_c_path="${include_path}/${mongoose_c}"

function download_file() {
  local path=$1
  local url=$2

  if [ ! -f "${path}" ]; then
    echo "Downloading ${url} to ${path}"
    curl -f -o "${path}" "${url}"
    if [ $? -eq 0 ]; then
      echo "Successfully downloaded ${url} to ${path}"
    else
      echo "Failed to download ${url}"
    fi
  else
    echo "Path ${path} already exists."
  fi
}

download_file "${mongoose_h_path}" "${mongoose_h_url}"
download_file "${mongoose_c_path}" "${mongoose_c_url}"
