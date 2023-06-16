ECHO OFF

ECHO Running preprocessor on main.cpp
clang++ -E main.cpp -o main.i
ECHO Preprocessing done. Output in main.i
