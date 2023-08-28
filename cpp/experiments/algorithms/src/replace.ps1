param (
  [string]$InFile,
  [string]$OutFile
)

# Documentation:
#
# The purpose of this script is to make clear distinction between the `User`
# questions and `ChatGPT` responses.
#
# To replace the `User` and `ChatGPT` tokens in a file and output them to a
# different file, invoke the script as follows:
#
# replace.bat -infile <input file> -outfile <output file>

$inFilePath = Join-Path $pwd $InFile
$outFilePath = Join-Path $pwd $OutFile

$content = Get-Content -Path $inFilePath -Raw

$content = $content -replace 'ChatGPT', "`n---`n`nChatGPT"
$content = $content -replace 'User', "`n---`n`nUser`n"

$content | Set-Content -Path $outFilePath
