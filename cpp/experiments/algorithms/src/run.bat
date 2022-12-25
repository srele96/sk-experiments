@REM take the filename of the c++ program with main function, compile and run it
clang++ -Wall -Wextra -Werror -Wshadow -Weffc++ -Wnon-virtual-dtor -pedantic -std=c++17 %1.cpp -o %1.exe && %1
