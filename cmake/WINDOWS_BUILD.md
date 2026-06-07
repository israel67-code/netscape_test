# Visual Studio Build Instructions for Netscape 5.0

## Prerequisites

### Required Software
- **Visual Studio 2019 or 2022** (Community, Professional, or Enterprise)
  - Desktop development with C++
  - CMake tools for Windows
- **CMake 3.15+** (or use VS built-in CMake)
- **Git** for version control
- **7-Zip or WinRAR** (optional, for manual archive extraction)

### Optional
- **Visual Studio Code** with C++ Extensions
- **Windows SDK 10.0+**

## Option 1: Using Visual Studio Built-in CMake (Recommended)

### Step 1: Open Project
1. Launch **Visual Studio 2019/2022**
2. Select **File → Open → Folder**
3. Navigate to and select your netscape_test repository

### Step 2: Configure
Visual Studio will automatically detect CMakeLists.txt:
1. Wait for VS to initialize CMake
2. Select **x64-Release** or **x64-Debug** from the build configuration dropdown
3. Right-click **CMakeLists.txt** → **Generate Cache**

### Step 3: Build
1. Select **Build → Build All** (or Ctrl+Shift+B)
2. Monitor the output window for progress
3. Wait for CEF download and compilation

### Step 4: Run
1. Select **Build → Select Startup Item → netscape.exe**
2. Press **F5** or **Debug → Start Debugging**

## Option 2: Using CMake GUI

### Step 1: Download CMake
If not already installed:
1. Download from https://cmake.org/download/
2. Run the installer
3. Choose "Add CMake to system PATH"

### Step 2: Configure with CMake GUI
1. Open **CMake GUI**
2. Set **Source code**: `C:/path/to/netscape_test`
3. Set **Build**: `C:/path/to/netscape_test/build`
4. Click **Configure**
5. Select **Visual Studio 16 2019** or **Visual Studio 17 2022**
6. Click **Finish** and wait for configuration
7. Click **Generate**

### Step 3: Open and Build
1. Click **Open Project** in CMake GUI
2. Or manually open `build/Netscape.sln`
3. In Visual Studio, select build configuration (Debug/Release)
4. Build → Build Solution (Ctrl+Shift+B)

### Step 4: Run
1. In Solution Explorer, right-click **netscape** → **Set as Startup Project**
2. Press **F5** or Debug → Start Debugging

## Option 3: Using Command Line (PowerShell)

```powershell
# Navigate to repository
cd C:\path\to\netscape_test

# Create build directory
mkdir build
cd build

# Configure (Visual Studio 2022 64-bit)
cmake .. -G "Visual Studio 17 2022" -A x64

# Build
cmake --build . --config Release --parallel 8

# Run tests
ctest --verbose

# Run browser
.\bin\Release\netscape.exe
```

For **Visual Studio 2019**:
```powershell
cmake .. -G "Visual Studio 16 2019" -A x64
```

## Build Configuration

### Debug Build
```powershell
cmake --build . --config Debug --parallel 8
```

### Release Build (Optimized)
```powershell
cmake --build . --config Release --parallel 8
```

### Rebuild from Scratch
```powershell
rmdir /s build
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release --parallel 8
```

## Advanced Options

### Use Static C Runtime
```powershell
cmake .. -G "Visual Studio 17 2022" -A x64 -DUSE_STATIC_RUNTIME=ON
```

### Disable Tests
```powershell
cmake .. -G "Visual Studio 17 2022" -A x64 -DBUILD_TESTS=OFF
```

### Custom Installation Directory
```powershell
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX="C:\netscape_install"
cmake --build . --config Release
cmake --install . --config Release
```

## What Gets Built

```
build/
├── bin/
│   ├── Debug/
│   │   ├── netscape.exe          # Debug executable
│   │   ├── netscape.pdb          # Debug symbols
│   │   └── netscape_test.exe     # Test executable
│   └── Release/
│       ├── netscape.exe          # Release executable
│       └── netscape_test.exe     # Test executable
├── lib/
│   ├── Debug/
│   │   ├── modern_renderer.lib
│   │   └── ...
│   └── Release/
│       └── ...
└── Netscape.sln                  # Visual Studio solution
```

## Troubleshooting

### Issue: "CMake not found"
**Solution**: Install CMake or add to PATH
```powershell
# Check if CMake is installed
cmake --version

# Add to PATH if needed
$env:Path += ";C:\Program Files\CMake\bin"
```

### Issue: "Visual Studio not found"
**Solution**: Install Visual Studio or specify version
```powershell
# List available generators
cmake --help

# Or install VS 2022 from https://visualstudio.microsoft.com/
```

### Issue: "CEF download fails"
**Solution**: Download manually
1. Go to https://github.com/chromiumembedded/cef-builds/releases
2. Download appropriate Windows binary (windows64 or windows32)
3. Extract to `build/deps/`
4. Re-run CMake configure

### Issue: "Out of memory during build"
**Solution**: Reduce parallel builds
```powershell
cmake --build . --config Release --parallel 2
```

### Issue: "Permission denied" or "Access violation"
**Solution**: Run PowerShell as Administrator
```powershell
# Right-click PowerShell → Run as Administrator
```

### Issue: "LNK1169: one or more multiply defined symbols"
**Solution**: Clean and rebuild
```powershell
cd build
rmdir /s CMakeFiles
rmdir /s CMakeCache.txt
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

## Performance

Expected build times (x64 Release):
- First build: **3-5 minutes** (includes CEF download ~2-3min)
- Incremental build: **30-60 seconds**
- Clean rebuild: **3-5 minutes**

Depends on:
- Internet speed (for CEF download)
- CPU cores and speed
- SSD vs HDD
- Antivirus software

## Environment Setup

### Set Default Generator
```powershell
# In your PowerShell profile
$env:CMAKE_GENERATOR = "Visual Studio 17 2022"
$env:CMAKE_GENERATOR_PLATFORM = "x64"
```

### PowerShell Alias for Quick Build
```powershell
# Add to PowerShell profile
function Build-Netscape {
    param([string]$Config = "Release")
    cmake --build build --config $Config --parallel 8
}

function Run-Netscape {
    param([string]$Config = "Release")
    .\build\bin\$Config\netscape.exe
}
```

## Testing

### Run All Tests
```powershell
cd build
ctest --verbose
```

### Run Specific Test
```powershell
ctest -N              # List all tests
ctest -R "Rendering" # Run tests matching pattern
```

### Debug a Test
```powershell
.\build\bin\Release\netscape_test.exe
```

## Additional Resources

- [CMake Documentation](https://cmake.org/documentation/)
- [Visual Studio C++ Documentation](https://docs.microsoft.com/en-us/cpp/)
- [CEF Documentation](https://bitbucket.org/chromiumembedded/cef/wiki/Home)
- [Windows SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk/)

## Support

For issues:
1. Check the **Troubleshooting** section above
2. Review **BUILD.md** in repository root
3. Check **INTEGRATION_GUIDE.md** for integration details
4. Enable verbose output: `cmake --build . --verbose`
