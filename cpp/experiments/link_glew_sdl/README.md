# Link GLEW and SDL

An experiment to link GLEW and SDL.

## Important

**DYNAMIC LIBRARIES MUST BE PLACED IN THE LOCATION OF EXECUTABLE!!!**

An alternative approach is to add it to wherever the executable searches for dynamic libraries on the system.

It seems it is common approach to deliver dynamic libraries in the directory of the executable. For example, World of Warcraft has dynamic libraries located next to the executable.

## Notes

Notes about problems I encountered when performing this experiment.

### Linking order is important

The following command to link SDL2, causes the error below the command:

```cmd
clang++ main.cpp -L./ -lSDL2 -lSDL2main -o main
```

```cmd
C:/msys64/ucrt64/bin/ld: .//SDL2main.lib(x64/Release/SDL_windows_main.obj):(.text$mn+0x84): undefined reference to `SDL_wcslen'
C:/msys64/ucrt64/bin/ld: .//SDL2main.lib(x64/Release/SDL_windows_main.obj):(.text$mn+0xa2): undefined reference to `SDL_iconv_string'
C:/msys64/ucrt64/bin/ld: .//SDL2main.lib(x64/Release/SDL_windows_main.obj):(.text$mn+0xb6): undefined reference to `SDL_strlen'
C:/msys64/ucrt64/bin/ld: .//SDL2main.lib(x64/Release/SDL_windows_main.obj):(.text$mn+0xf3): undefined reference to `SDL_memcpy'
C:/msys64/ucrt64/bin/ld: .//SDL2main.lib(x64/Release/SDL_windows_main.obj):(.text$mn+0xfb): undefined reference to `SDL_free'
C:/msys64/ucrt64/bin/ld: .//SDL2main.lib(x64/Release/SDL_windows_main.obj):(.text$mn+0x122): undefined reference to `SDL_SetMainReady'
C:/msys64/ucrt64/bin/ld: .//SDL2main.lib(x64/Release/SDL_windows_main.obj):(.text$mn+0x12e): undefined reference to `SDL_main'
C:/msys64/ucrt64/bin/ld: .//SDL2main.lib(x64/Release/SDL_windows_main.obj):(.text$mn+0x18e): undefined reference to `SDL_ShowSimpleMessageBox'
```

However, the following command linked without problems:

```cmd
clang++ main.cpp -L./ -lSDL2main -lSDL2 -o main
```

### SDL requires specific signature for main function

SDL2 requires the following signature:

```cpp
int main(int argv, char** args) {
  // ...
}
```

Without signature like this, SDL2 causes an error:

```txt
undefined reference to `SDL_main`
```

[Here is stackoverflow answer.](https://stackoverflow.com/questions/10803918/undefined-reference-to-sdl-main)

### Linking against `opengl32.lib`

This library `opengl32.lib` is delivered with operating system. GLEW allows us to use latest OpenGL functions. Therefore we have to against `opengl32.lib` because we are using the code from there as well.

### Linking against dynamic libraries for GLEW and SDL

The reason dynamic libraries are linked without any code provided in this example is that the compiled binary is using dynamic libraries relative to the executable. An alternative would be to place dynamic libraries in `C:\Windows\System32`, but that is bad practice because any program can run them. If there is any vulnerability within them it can be exploited.

### Using better includes

I would like to include glew and SDL2 libraries as follows:

```cpp
#include "GL/glew.h"
#include "SDL2/SDL.h"
```

I had to tell the compiler where to search for included files.

The full command:

```cmd
clang++ main.cpp -L./ -lSDL2main -lSDL2 -lglew32 -lopengl32 -I./deps/GLEW-2.2.0/include -I./deps/SDL2-2.26.2/include -o main
```

One directory to search for includes:

```txt
-I./deps/GLEW-2.2.0/include
```

Another directory to search for includes:

```txt
-I./deps/SDL2-2.26.2/include
```

The reason i said _one and another directory_ is because it tells where to search for included files. Imagine the compiler as a person who has a list of places to visit in town. But we suggest one or more places to visit. This flag tells the compiler exactly that.

### Explanation of the compilation command

- Search for lib files in: `-L./deps/GLEW-2.2.0/lib`
- Search for lib files in: `-L./deps/SDL2-2.26.2/lib`
- Link SDL2main.lib: `-lSDL2main`
- Link SDL2.lib: `-lSDL2`
- Link glew32.lib: `-lglew32`
- The `opengl32.lib` file is distributed with operating system. There is no need to add it to the project, link flag: `-lopengl32`
- Tell the compiler where to search for included glew headers: `-I./deps/GLEW-2.2.0/include`
- Tell the compiler where to search for included SDL2 headers: `-I./deps/SDL2-2.26.2/include`
