# Link GLEW and SDL

An experiment to link GLEW and SDL.

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
