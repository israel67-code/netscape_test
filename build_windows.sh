#!/bin/bash
# Windows Build Script using CMake and Visual Studio
# Usage: ./build_windows.sh [Release|Debug]

set -e

BUILD_TYPE=${1:-Release}
BUILD_DIR="build"

echo "=== Netscape 5.0 Windows Build ==="
echo "Build type: $BUILD_TYPE"
echo ""

# Check if CMake is available
if ! command -v cmake &> /dev/null; then
    echo "Error: CMake not found. Please install CMake."
    exit 1
fi

echo "CMake version:"
cmake --version
echo ""

# Create build directory
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir -p "$BUILD_DIR"
fi

cd "$BUILD_DIR"

# Detect Visual Studio version
if [ -f "Netscape.sln" ]; then
    echo "Build files already present."
else
    echo "Configuring CMake..."
    # Try Visual Studio 2022 first, fall back to 2019
    if cmake .. -G "Visual Studio 17 2022" -A x64 2>/dev/null; then
        echo "Configured for Visual Studio 2022"
    elif cmake .. -G "Visual Studio 16 2019" -A x64 2>/dev/null; then
        echo "Configured for Visual Studio 2019"
    else
        echo "Error: Visual Studio not found. Please install Visual Studio 2019 or later."
        exit 1
    fi
fi

echo "Building $BUILD_TYPE configuration..."
cmake --build . --config $BUILD_TYPE --parallel 8

echo ""
echo "Build complete!"
echo ""
echo "Output files:"
echo "  Executable: ./bin/$BUILD_TYPE/netscape.exe"
echo "  Tests:      ./bin/$BUILD_TYPE/netscape_test.exe"
echo ""
echo "To run tests:"
echo "  ctest --verbose"
echo ""
echo "To run browser:"
echo "  ./bin/$BUILD_TYPE/netscape.exe"
