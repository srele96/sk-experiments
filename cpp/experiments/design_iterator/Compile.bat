@ECHO OFF
SETLOCAL

SET __dirname=%~dp0
@REM Use filename so that .bat and .ps1 script can have the same name and all
@REM we need to do is rename both. The advantage of this approach is that when
@REM the script name changes we don't have to write the name file name inside
@REM this .bat file because it already uses its current name.
SET __filename=%~n0
SET script=%__dirname%%__filename%.ps1

POWERSHELL -ExecutionPolicy Bypass -File %script% %*

ENDLOCAL
