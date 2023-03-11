###############################################################################
# In order to use mongoose library I have to build static library and link it
# to my project.
#
# I tried to add `include/mongoose/mongoose.c` to CMakeLists.txt in
# add_executable() but it didn't work. After that I decided to build it as
# static library and link it as static library.
###############################################################################

$__dirname = $PSScriptRoot
$includeDir = "include"
$includePath = Join-Path $__dirname $includeDir

$libDir = "lib"

$mongooseDir = "mongoose"
$mongoosePath = Join-Path $includePath $mongooseDir

$mongooseSource = "mongoose.c"
$mongooseSourcePath = Join-Path $mongoosePath $mongooseSource

$mongooseObject = "mongoose.o"
$mongooseObjectPath = Join-Path $mongoosePath $mongooseObject

$mongooseLibPath = Join-Path $mongoosePath $libDir

$mongooseStaticLib = "mongoose.lib"
$mongooseStaticLibPath = Join-Path $mongooseLibPath $mongooseStaticLib

$buildMongooseObject = clang -c $mongooseSourcePath -o $mongooseObjectPath

# Provide information on what is going on so the script doesn't run and exit
# with a blank screen.
Write-Host "----"
Write-Host "Creating object file:"
Write-Host "Building:" $mongooseSourcePath "`nTo:" $mongooseObjectPath
$buildMongooseObject
Write-Host "----`n"

# The path creation errors if the path already exists.
if (-not (Test-Path $mongooseLibPath)) {
  Write-Host "Creating:" $mongooseLibPath
  New-Item -ItemType Directory -Path $mongooseLibPath | Out-Null
}

Write-Host "----"
Write-Host "Creating static library:"
$buildMongooseStaticLib = llvm-ar rcs $mongooseStaticLibPath $mongooseObjectPath
Write-Host "Building:" $mongooseStaticLibPath "`nFrom:" $mongooseObjectPath
$buildMongooseStaticLib
Write-Host "----`n"
