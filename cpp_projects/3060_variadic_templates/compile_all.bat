@echo off
REM Compile all .cpp files in this folder using g++ and C++11

for %%f in (*.cpp) do (
    echo Compiling %%f ...
    g++ -std=c++11 -Wall -Wextra -pedantic -o "%%~nf.exe" "%%f"
)
echo All files compiled.
pause
