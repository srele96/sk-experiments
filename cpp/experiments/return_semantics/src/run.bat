@ECHO OFF

SET file_name=%1.cpp
SET executable=%1.exe
SET out_dir=build\
SET out_path=%out_dir%%executable%

ECHO Compiling %file_name%

@REM I was getting error that the syntax is incorrect and google search gave me
@REM this solution on how to check if directory exists.
@REM https://stackoverflow.com/questions/21033801/checking-if-a-folder-exists-using-a-bat-file
IF NOT EXIST %out_dir% (
  ECHO Creating %out_dir% directory...
  MKDIR %out_dir%
)

clang++ -std=c++17 %file_name% -o %out_path%

IF %ERRORLEVEL%==0 (
  ECHO Running %out_path%
  ECHO =================
  %out_path%
)
