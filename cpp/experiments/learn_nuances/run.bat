@ECHO OFF

ECHO Compiling %1.cpp
clang++ %1.cpp -o %1
ECHO Running %1
%1
