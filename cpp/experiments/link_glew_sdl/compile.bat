@ECHO OFF

clang++ main.cpp -L./deps/GLEW-2.2.0/lib -L./deps/SDL2-2.26.2/lib -lSDL2main -lSDL2 -lglew32 -lopengl32 -I./deps/GLEW-2.2.0/include -I./deps/SDL2-2.26.2/include -o main
