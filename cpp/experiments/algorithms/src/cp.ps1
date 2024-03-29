###############################################################################
#
# Competitive Programming compilation flags
#
# https://cses.fi/book/book.pdf
#
###############################################################################

$linebreak = "----------------"
Write-Host $linebreak

$outDir = "build"

if (-Not (Test-Path $outDir)) {
  Write-Host "Creating $outDir directory"
  New-Item -ItemType Directory -Path $outDir
  Write-Host $linebreak
}

$filename = $args[0]
$file = "$filename.cpp"
$out = "$outDir\$filename.exe"

if ($filename) {
  Write-Host "Compiling $file to $out."
  g++ -std=c++20 -O2 -Wall $file -o $out
  Write-Host "Done."
  Write-Host $linebreak

  if ($LastExitCode -eq 0) {
    Write-Host "Running $out.`n"
    Invoke-Expression $out
  }
}
else {
  Write-Host "No filename provided."
  Write-Host $linebreak
  exit 1
}
