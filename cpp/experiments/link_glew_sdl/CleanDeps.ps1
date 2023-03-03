# Helper to clean up the dependencies before running .\SetupDeps to set them up.

$items = @(
  "glew32.dll"
  "SDL2.dll"
  "deps"
)

$itemList = $items | ForEach-Object { "`n  - $_" }
Write-Host "Removing the following items from the project root:" + $itemList

foreach ($item in $items) {
  $itemPath = Join-Path $PSScriptRoot $item
  if (Test-Path -Path $itemPath) {
    Write-Host "Removing: $itemPath"
    Remove-Item -Path $itemPath -Recurse -Force
  }
}
