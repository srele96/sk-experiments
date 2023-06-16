@REM take the filename of the c++ program with main function, compile and run it
mkdir build
clang++ -std=c++17 %1.cpp -o build\%1.exe && build\%1
