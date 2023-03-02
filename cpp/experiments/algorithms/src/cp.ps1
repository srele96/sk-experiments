###############################################################################
#
# Competitive Programming compilation flags
#
# https://cses.fi/book/book.pdf
#
###############################################################################

$linebreak = "--------"
Write-Host $linebreak

$outDir = "build"

if (!(Test-Path $outDir)) {
  Write-Host "Creating build directory"
  New-Item -ItemType Directory -Path build
}

$filename = $args[0]
$file = "$filename.cpp"
$out = "$outDir\$filename.exe"

if ($filename) {
  Write-Host "Compiling $file to $out."
  g++ -std=c++11 -O2 -Wall $file -o $out
  Write-Host "Done."
  Write-Host $linebreak

  if ($LastExitCode -eq 0) {
    # print "Running $out." with newline after
    Write-Host "Running $out.`n"
    Invoke-Expression $out
  }
}
else {
  Write-Host "No filename provided."
  Write-Host $linebreak
  exit 1
}
