@ECHO OFF

SET OUT=out.cpp

ECHO Generating Abstract Syntax Tree (AST)...

clang++ -Xclang -ast-print -fsyntax-only main.cpp > %OUT%

IF %ERRORLEVEL% EQU 0 (
  ECHO Done. Open %OUT% to see the Abstract Syntax Tree ^(AST^).
)
@REM Let compiler handle errors.
