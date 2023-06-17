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

httplib_h_url="https://raw.githubusercontent.com/yhirose/cpp-httplib/v0.12.6/httplib.h"
httplib_h="httplib.h"
httplib_h_path="${include_path}/${httplib_h}"

if [ ! -f "${httplib_h_path}" ]; then
  echo "Downloading ${httplib_h_url} to ${httplib_h_path}"
  curl -f -o "${httplib_h_path}" "${httplib_h_url}"
  if [ $? -eq 0 ]; then
    echo "Download succeeded."
  else
    echo "Download failed."
  fi
else
  echo "${httplib_h} already exists."
fi
