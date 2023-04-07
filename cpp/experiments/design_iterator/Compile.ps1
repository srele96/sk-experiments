# Must be on top of the file, doesn't work otherwise.
param (
  [Parameter(Mandatory = $true)]
  [String]
  $FileName,

  [switch]
  $DebugMode
)

function Get-Flags {
  param(
    [Parameter(Mandatory = $true)]
    [bool]
    $DebugMode
  )

  $debugFlags = @('-O0', '-g3')
  $regularFlags = @('-O2')
  $flags = @('-std=c++17', '-Wall')
  $flags += if ($DebugMode) { $debugFlags } else { $regularFlags }

  return $flags -join ' '
}

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

  if ($DebugMode) {
    Write-Host "Building in debug mode."
  }
  else {
    Write-Host "Building in regular mode."
  }

  $combineFlags = Get-Flags $DebugMode
  Write-Host "Flags: $combineFlags"

  # Wrap in a string and use Invoke-Expression because flag merging doesn't
  # work withouth it.
  $compile = "clang++ $combineFlags $file -o $outPath"
  Invoke-Expression $compile

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
