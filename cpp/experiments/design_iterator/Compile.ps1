param (
  [Parameter(Mandatory = $true)]
  [String]
  $FileName
)

$__dirname = $PSScriptRoot
$buildDirName = "build"
$buildDirPath = Join-Path $__dirname $buildDirName

Write-Host "Location: $buildDirPath"
Write-Host "Initializing build script..."

# Make sure we have a filename before we proceed.
if ($FileName) {
  $buildDirExist = Test-Path $buildDirPath
  if (-not $buildDirExist) {
    Write-Host "Creating $buildDirName directory..."
    New-Item -ItemType Directory -Path $buildDirPath
  }
  else {
    Write-Host "Directory already exists: $buildDirName"
  }

  $file = "$FileName.cpp"
  $executable = "$FileName.exe"
  $relativeOutPath = Join-Path $buildDirName $executable
  $outPath = Join-Path $buildDirPath $executable

  Write-Host "Compiling $file to $relativeOutPath"
  $compile = clang++ -std=c++17 -O2 -Wall $file -o $outPath
  $compile

  if ($LastExitCode -eq 0) {
    Write-Host "Compilation done: $relativeOutPath"
  }
  else {
    Write-Host "Compilation failed."
    exit $LastExitCode
  }
}
else {
  Write-Host "No filename provided."
  exit 1
}
