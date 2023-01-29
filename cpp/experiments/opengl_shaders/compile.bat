@ECHO OFF

@REM LINKER SEARCH PATHS
SET link_search_flag=-L
SET link_search_path_sdl=%link_search_flag%./deps/SDL2-2.26.2/lib
SET link_search_path_glew=%link_search_flag%./deps/GLEW-2.2.0/lib
SET link_search_paths=%link_search_path_sdl% %link_search_path_glew%

@REM LINKER INCLUDES
SET link_flag=-l
SET link_sdl=%link_flag%SDL2main -lSDL2
SET link_glew=%link_flag%glew32
SET link_opengl=%link_flag%opengl32
SET link_libs=%link_sdl% %link_glew% %link_opengl%

@REM COMPILER INCLUDE PATHS
SET include_flag=-I
SET include_glew=%include_flag%./deps/GLEW-2.2.0/include
SET include_sdl=%include_flag%./deps/SDL2-2.26.2/include
SET include_paths=%include_glew% %include_sdl%

@REM SOURCE FILES
SET file_name=main
SET file_extension=.cpp
SET file=%file_name%%file_extension%

@REM OUTPUT
SET out_name=%file_name%
SET out_extension=.exe
SET out=%out_name%%out_extension%

ECHO Compiling %file%...

clang++ %file% %link_search_paths% %link_libs% %include_paths% -o %out%

@REM Check if compilation succeeded
IF %ERRORLEVEL% EQU 0 (
  ECHO Compilation succeeded! Type ./%out% to run.
)
@REM Let compiler handle failure
