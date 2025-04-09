@echo off
echo Formatting all C++ files...

REM Find all .cpp and .h files and format them, excluding Extern directory
for /r %%f in (*.cpp *.h) do (
    echo %%f | findstr /i /c:"\\Extern\\" >nul
    if errorlevel 1 (
        echo Formatting %%f
        clang-format -i -style=file "%%f"
    ) else (
        echo Skipping %%f
    )
)

echo Done!
pause 