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

$flag = $args[0]

$flagHelp = "--help"
$flagStatic = "--static"
$flagDynamic = "--dynamic"
$flagBoth = "--both"
$availableFlags = @($flagHelp, $flagStatic, $flagDynamic, $flagBoth)

# function that takes expression as a string and executes it
function PrintAndRun {
  param (
    [string]$expression
  )

  Write-Host $expression
  Invoke-Expression $expression
}

function RunAndPrintOutput {
  param (
    [string]$expression
  )

  $executable = ".\main.exe"
  $compile = "$expression $executable"
  PrintAndRun $compile

  PrintAndRun $executable

  Write-Host "Cleaning up the $executable..."
  Remove-Item $executable -ErrorAction SilentlyContinue
}

function RunDynamic {
  $compile = "clang++ -L. -lwhatever main.cpp -o"
  RunAndPrintOutput $compile
}

function RunStatic {
  $compile = "clang++ main.cpp whatever_static.lib -o"
  RunAndPrintOutput $compile
}

$messageRunWithStaticLinking = "Running with static linking..."
$messageRunWithDynamicLinking = "Running with dynamic linking..."

switch ($flag) {
  $flagHelp {
    Write-Host "Available flags:"
    foreach ($availableFlag in $availableFlags) {
      Write-Host "  $availableFlag"
    }
  }
  $flagStatic {
    Write-Host $messageRunWithStaticLinking
    RunStatic
  }
  $flagDynamic {
    Write-Host $messageRunWithDynamicLinking
    RunDynamic
  }
  $flagBoth {
    Write-Host $messageRunWithStaticLinking
    RunStatic
    Write-Host $messageRunWithDynamicLinking
    RunDynamic
  }
  default {
    Write-Host "Flag '$flag' is not recognized, use '$flagHelp' to see available flags"
  }
}
