@ECHO OFF

SET out=out.exe

REM Compiling...
clang++ %1 -o %out%

IF %ERRORLEVEL% EQU 0 (
  ECHO Compilation successful
  ECHO Running %out%
  ECHO =================
  %out%
)
