@ECHO off

@REM make this runnable from anywhere and reference the file location
SET __DIRNAME=%~dp0
SET CREATE_CONTENT=%__DIRNAME%\create_content.ps1

powershell -ExecutionPolicy Bypass -File %CREATE_CONTENT% %*
