@ECHO OFF

SET out=out.exe

REM Compiling...
clang++ %1 -o %out%

if %ERRORLEVEL% EQU 0 (
  ECHO Compilation successful
  ECHO Running %out%
  ECHO =================
  %out%
)
