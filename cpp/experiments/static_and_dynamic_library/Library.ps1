# If the current location is not script location, write an error message and
# terminate to avoid invocation from wrong location and to avoid handling of
# path where the script lives and location it gets executed from.
$scriptAbsolutePath = (Get-Item $PSScriptRoot).FullName
$invokedFromIncorrectDirectory = "$PWD" -ne "$scriptAbsolutePath"
if ($invokedFromIncorrectDirectory) {
  Write-Error "This script must be invoked from the '$scriptAbsolutePath' directory"

  $errorCode = 1
  exit $errorCode
}

$file = "whatever.cpp"

$dll = "whatever.dll"
$obj = "whatever.o"
$lib = "whatever_static.lib"

if ($args[0] -eq "--clean") {
  Write-Host "Cleaning up..."
  $tryingToCleanUp = "Trying to clean up:"

  Write-Host $tryingToCleanUp $dll
  Remove-Item $dll -ErrorAction SilentlyContinue

  Write-Host $tryingToCleanUp $lib
  Remove-Item $obj -ErrorAction SilentlyContinue

  Write-Host $tryingToCleanUp $obj
  Remove-Item $lib -ErrorAction SilentlyContinue
}
else {
  Write-Host "Starting build..."
  $building = "Building:"
  $creating = "Creating:"
  $cleaning = "Cleaning up:"

  Write-Host $building $dll
  clang++ -shared -o $dll $file

  Write-Host $building $obj
  clang++ -c $file -o $obj

  Write-Host $creating $lib
  llvm-ar rcs $lib $obj

  Write-Host $cleaning $obj
  Remove-Item $obj
}
