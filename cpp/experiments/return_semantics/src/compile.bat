@ECHO OFF

SET file_name=%1.cpp
SET executable=%1.exe
SET out_dir=build
SET out_path=%out_dir%\%executable%

ECHO Compiling %file_name%

IF NOT EXIST %outdir% (
  MKDIR %outdir%
)

clang++ -std=c++17 %file_name% -o %out_path%

IF %ERRORLEVEL%==0 (
  ECHO Running %out_path%
  ECHO =================
  %out_path%
)
