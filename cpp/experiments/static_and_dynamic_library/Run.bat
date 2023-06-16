@ECHO OFF
@REM forward all arguments to the Run.ps1 script
powershell -ExecutionPolicy Bypass -File Run.ps1 %*
