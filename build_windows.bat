@echo off
REM Windows Batch Build Script
REM Usage: build_windows.bat [Release|Debug]

setlocal enabledelayedexpansion

set BUILD_TYPE=%1
if "%BUILD_TYPE%"==" " set BUILD_TYPE=Release

echo.
echo === Netscape 5.0 Windows Build ===
echo Build type: %BUILD_TYPE%
echo.

REM Check if CMake is available
where cmake >nul 2>nul
if errorlevel 1 (
    echo Error: CMake not found. Please install CMake.
    pause
    exit /b 1
)

echo CMake version:
cmake --version
echo.

REM Create build directory
if not exist "build" (
    echo Creating build directory...
    mkdir build
)

cd build

REM Check if solution already exists
if exist "Netscape.sln" (
    echo Build files already present.
) else (
    echo Configuring CMake...
    REM Try Visual Studio 2022 first
    cmake .. -G "Visual Studio 17 2022" -A x64
    if errorlevel 1 (
        REM Fall back to Visual Studio 2019
        cmake .. -G "Visual Studio 16 2019" -A x64
        if errorlevel 1 (
            echo Error: Visual Studio not found. Please install Visual Studio 2019 or later.
            pause
            exit /b 1
        )
    )
)

echo Building %BUILD_TYPE% configuration...
cmake --build . --config %BUILD_TYPE% --parallel 8

if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Build complete!
echo.
echo Output files:
echo   Executable: bin\%BUILD_TYPE%\netscape.exe
echo   Tests:      bin\%BUILD_TYPE%\netscape_test.exe
echo.
echo To run tests:
echo   ctest --verbose
echo.
echo To run browser:
echo   bin\%BUILD_TYPE%\netscape.exe
echo.
pause
