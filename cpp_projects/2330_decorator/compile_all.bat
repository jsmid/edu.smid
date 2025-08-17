@echo off
REM filepath: c:\Documents\cpp_projects\0201_hellocpp\build_all.bat
REM Batch file to compile all .cpp files in the current folder using g++

REM Set the compiler path if needed (uncomment and edit the next line)
REM set PATH=C:\MinGW\bin;%PATH%

for %%f in (*.cpp) do (
    echo Compiling %%f ...
    g++ -std=c++11 -o "%%~nf.exe" "%%f"
)
echo All files compiled.
pause