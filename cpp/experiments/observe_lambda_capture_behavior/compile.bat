@ECHO OFF

SETLOCAL

SET file=main.cpp
SET out=main

clang++ -std=c++17 %file% -o %out%

IF ERRORLEVEL 1 (
  ECHO Error compiling %file%.
) ELSE (
  ECHO Compilation successful. Run .\%out% to see the output.
)

ENDLOCAL
