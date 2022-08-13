@REM use suggested strict flags for compilation
@REM https://github.com/cpp-best-practices/cppbestpractices/blob/master/02-Use_the_Tools_Available.md#gcc--clang
clang++ -Wall -Wextra -Wshadow -Weffc++ -Wnon-virtual-dtor -pedantic main.cpp -o main.exe && main
