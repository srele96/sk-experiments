@ECHO OFF
@REM forward all arguments to the CreateLibrary.ps1 script
powershell -ExecutionPolicy Bypass -File CreateLibrary.ps1 %*
