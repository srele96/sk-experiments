@ECHO OFF
@REM Intermedium script to run the powershell script and forward the arguments.
powershell -ExecutionPolicy Bypass -File cp.ps1 %*
