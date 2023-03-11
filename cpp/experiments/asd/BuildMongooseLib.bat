@ECHO OFF
SETLOCAL

SET __dirname=%~dp0
SET __filename=%~n0
SET script=%__dirname%%__filename%.ps1

POWERSHELL -ExecutionPolicy Bypass -File %script%

ENDLOCAL
