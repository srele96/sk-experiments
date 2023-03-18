###############################################################################
# In order to use mongoose library I have to build static library and link it
# to my project.
#
# I tried to add `include/mongoose/mongoose.c` to CMakeLists.txt in
# add_executable() but it didn't work. After that I decided to build it as
# static library and link it as static library.
###############################################################################

# TODO(improve logging): Logging is hard-coded
# Changes in one place requires change on every other place. Leave as is, the
# next time this file requires change, logging should be improved first.
#
# TODO(improve log clarity): Log messages seem to clutter output
# Both TODOs should be done together.

$__dirname = $PSScriptRoot
$includeDir = "include"
$includePath = Join-Path $__dirname $includeDir

$mongooseDir = "mongoose"
$mongoosePath = Join-Path $includePath $mongooseDir

$mongooseSourceURL = 'https://raw.githubusercontent.com/cesanta/mongoose/7.9/mongoose.c'
$mongooseSource = "mongoose.c"
$mongooseSourcePath = Join-Path $mongoosePath $mongooseSource

$mongooseHeaderURL = 'https://raw.githubusercontent.com/cesanta/mongoose/7.9/mongoose.h'
$mongooseHeader = 'mongoose.h'
$mongooseHeaderPath = Join-Path $mongoosePath $mongooseHeader

$mongooseObject = "mongoose.o"
$mongooseObjectPath = Join-Path $mongoosePath $mongooseObject

$libDir = "lib"
$mongooseLibPath = Join-Path $mongoosePath $libDir

$mongooseStaticLib = "mongoose.lib"
$mongooseStaticLibPath = Join-Path $mongooseLibPath $mongooseStaticLib

# Provide information on what is going on so the script doesn't run and exit
# with a blank screen.

if (Test-Path $includePath) {
  Write-Host $includePath already exists... proceeding...
}
else {
  Write-Host creating $includePath...
  New-Item -ItemType Directory -Path $includePath | Out-Null
}

if (Test-Path $mongoosePath) {
  Write-Host $mongoosePath already exists... proceeding...
}
else {
  Write-Host creating $mongoosePath...
  New-Item -ItemType Directory -Path $mongoosePath | Out-Null
}

if (Test-Path $mongooseSourcePath) {
  Write-Host $mongooseSourcePath already exists... skipping download...
}
else {
  Write-Host "----"
  Write-Host "Creating:" $mongooseSource
  Write-Host "Downloading:" $mongooseSourceURL "`nTo:" $mongooseSourcePath
  Write-Host "----`n"
  Invoke-WebRequest -Uri $mongooseSourceURL -OutFile $mongooseSourcePath
}

if (Test-Path $mongooseHeaderPath) {
  Write-Host $mongooseHeaderPath already exists... skipping download...
}
else {
  Write-Host "----"
  Write-Host "Creating:" $mongooseHeader
  Write-Host "Downloading:" $mongooseHeaderURL "`nTo:" $mongooseHeaderPath
  Write-Host "----`n"
  Invoke-WebRequest -Uri $mongooseHeaderURL -OutFile $mongooseHeaderPath
}

Write-Host "----"
Write-Host "Creating:" $mongooseObject
Write-Host "Building:" $mongooseSourcePath "`nTo:" $mongooseObjectPath
$buildMongooseObject = clang -c $mongooseSourcePath -o $mongooseObjectPath
$buildMongooseObject
Write-Host "----`n"

if (Test-Path $mongooseLibPath) {
  Write-Host $mongooseLibPath already exists... proceeding...
}
else {
  Write-Host creating $mongooseLibPath...
  New-Item -ItemType Directory -Path $mongooseLibPath | Out-Null
}

Write-Host "----"
Write-Host "Creating:" $mongooseStaticLib
Write-Host "Building:" $mongooseStaticLibPath "`nFrom:" $mongooseObjectPath
$buildMongooseStaticLib = llvm-ar rcs $mongooseStaticLibPath $mongooseObjectPath
$buildMongooseStaticLib
Write-Host "----`n"
