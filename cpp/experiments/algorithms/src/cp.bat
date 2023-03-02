@REM Competitive Programming compilation flags
@REM https://cses.fi/book/book.pdf

@REM Don't print out the contents of this file.
@ECHO OFF

@REM If %1 is empty, go to end and don't compile
IF "%1"=="" GOTO NO_FILE

ECHO ----
mkdir build

ECHO Compiling %1.cpp to build\%1
g++ -std=c++11 -O2 -Wall %1.cpp -o build\%1

ECHO Running build\%1
ECHO ----

build\%1
GOTO DONE

:NO_FILE
ECHO ----
ECHO No file specified.

:END
ECHO Done.
ECHO ----
