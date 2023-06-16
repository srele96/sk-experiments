@ECHO off
@REM powershell wrapper to make powershell script runnable in command prompt

@REM Use __dirname to refer other files relative to this script.
@REM https://stackoverflow.com/questions/3827567/how-to-get-the-path-of-the-batch-script-in-windows
SET __dirname=%~dp0
SET setupDeps=%__dirname%SetupDeps.ps1

POWERSHELL -ExecutionPolicy Bypass -File %setupDeps%
