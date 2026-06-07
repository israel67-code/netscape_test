# CEF-Based Netscape Build Instructions

## Quick Start

### Prerequisites
- Visual Studio 2022 or 2019
- CEF Binary (you already have this at `C:\Users\Alessio123\Desktop\rfd\deps\cef_binary_148.0.10+g7ee53f5+chromium-148.0.7778.218_windows64`)
- CMake 3.15+

### Build Steps

```bash
cd C:\Users\Alessio123\Desktop\rfd
rmdir /s /q build
mkdir build
cd build

cmake .. -G "Visual Studio 18 2026" -A x64 -DCEF_ROOT="C:\Users\Alessio123\Desktop\rfd\deps\cef_binary_148.0.10+g7ee53f5+chromium-148.0.7778.218_windows64"

cmake --build . --config Release --parallel 8
```

### Run

```bash
.\bin\Release\netscape.exe
```

## What This Build Does

1. **Links against real CEF libraries** - Uses your CEF 148.0.10 installation
2. **Implements CEF Client** - Proper CEF app and client classes
3. **Creates a browser window** - Launches Chromium browser embedded in Netscape
4. **Loads a webpage** - Opens https://www.example.com by default

## Key Changes

- Replaced stub implementations with real CEF-based code
- `NetscapeApp` - CEF application class
- `SimpleClient` - CEF browser client
- `RendererBridge` - Wrapper for CEF functionality
- `main.cc` - CEF initialization and browser creation

## Troubleshooting

### Missing libcef.lib

Ensure your CEF folder has:
```
cef_binary_148.0.10+.../
├── Release/
│   └── libcef.lib
└── libcef_dll_wrapper/
    └── Release/
        └── cef_dll_wrapper.lib
```

### Runtime DLL Errors

Copy CEF DLLs to the output directory:
```bash
copy "%CEF_ROOT%\Release\*.dll" .\bin\Release\
```

### Compiler Errors

If you get CEF-related compile errors:
1. Check CEF_ROOT path is correct
2. Ensure CEF version matches (148.0.10+)
3. Clean and rebuild: `cmake --build . --config Release --clean-first`

## Next Steps

After building:
1. Run the browser
2. Customize the URL in `cmd/main.cc` line ~100
3. Add more CEF features as needed
