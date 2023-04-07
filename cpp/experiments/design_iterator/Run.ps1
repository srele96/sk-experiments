$__dirname = $PSScriptRoot
$buildDirName = "build"
$buildDirPath = Join-Path $__dirname $buildDirName

Write-Host "Location: $buildDirPath"
Write-Host "Initializing build script..."

$fileName = $args[0]

# Make sure we have a filename before we proceed.
if ($fileName) {
  $buildDirExist = Test-Path $buildDirPath
  if (-not $buildDirExist) {
    Write-Host "Creating $buildDirName directory..."
    New-Item -ItemType Directory -Path $buildDirPath
  }
  else {
    Write-Host "Directory already exists: $buildDirName"
  }

  $file = "$fileName.cpp"
  $executable = "$fileName.exe"
  $relativeOutPath = Join-Path $buildDirName $executable
  $outPath = Join-Path $buildDirPath $executable

  Write-Host "Compiling $file to $relativeOutPath"
  $compile = clang++ -std=c++17 -O2 -Wall $file -o $outPath
  $compile

  if ($LastExitCode -eq 0) {
    Write-Host "Done. Running: $relativeOutPath"
    Invoke-Expression $outPath
  }
  else {
    Write-Host "Compilation failed."
  }
}
else {
  Write-Host "No filename provided."
  exit 1
}
