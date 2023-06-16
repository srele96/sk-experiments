@ECHO OFF
SETLOCAL

@REM Always use directory the file lives in.
SET __dirname=%~dp0

SET file=client.cpp
SET executable=client.exe
SET include_path=%__dirname%include
SET lib_path=%__dirname%include\mongoose\lib
SET file_path=%__dirname%%file%
SET executable_path=%__dirname%%executable%

@REM The linker indeed IS extremely touchy and I'm beyond annoyed.
@REM https://stackoverflow.com/questions/22314120/imp-link-errors-using-g-running-under-mingw
clang++ -std=c++17 -I%include_path% -L%lib_path% %file_path% -o %executable_path% -lmongoose -lws2_32

IF ERRORLEVEL 1 (
  ECHO Failed to compile %%
) Else (
  ECHO Successfully compiled %file% to %executable%
  ECHO Run the program:
  ECHO  1. cd %__dirname%
  ECHO  2. .\%executable%
)

ENDLOCAL
