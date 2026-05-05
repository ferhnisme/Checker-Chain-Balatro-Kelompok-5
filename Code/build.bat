@echo off
REM Compile the project
g++ -o main *.cpp ../Checkers/*.cpp

REM Clean up object files
del *.o 2>nul
del ..\Checkers\*.o 2>nul

echo Build complete! Executable: main.exe
