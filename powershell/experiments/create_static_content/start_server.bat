@ECHO off

@REM make this runnable from anywhere and reference the file location
SET __DIRNAME=%~dp0
SET START_SERVER=%__DIRNAME%\start_server.ps1

powershell -ExecutionPolicy Bypass -File %START_SERVER% %*
