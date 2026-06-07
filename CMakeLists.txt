cmake_minimum_required(VERSION 3.15)
project(NetscapeBrowser VERSION 5.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ============================================================================
# Platform Detection
# ============================================================================

if(WIN32)
    set(WINDOWS TRUE)
    message(STATUS "Windows platform detected")
elseif(APPLE)
    set(MACOS TRUE)
    message(STATUS "macOS platform detected")
elseif(UNIX AND NOT APPLE)
    set(LINUX TRUE)
    message(STATUS "Linux platform detected")
endif()

# ============================================================================
# Compiler Configuration
# ============================================================================

if(MSVC)
    # Visual Studio / MSVC specific flags
    add_compile_options(/W4 /WX /MP)  # Warning level 4, warnings as errors, multiprocessor build
    add_compile_options(/std:c++17)   # C++17 standard
    add_compile_options(/EHsc)        # Exception handling
    
    # Release optimizations
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Oi /Ot /GL")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
    
    # Debug symbols
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od /RTC1")
    
    # Disable specific warnings if needed
    add_compile_options(/wd4267)  # 'var': conversion from 'size_t' to 'type'
    add_compile_options(/wd4244)  # 'conversion': conversion from 'type1' to 'type2'
else()
    # GCC/Clang flags
    add_compile_options(-Wall -Wextra -Werror -fPIC)
    if(APPLE)
        add_compile_options(-fno-common)
    endif()
endif()

# ============================================================================
# Output Directories
# ============================================================================

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Windows-specific output
if(WINDOWS)
    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin/${OUTPUTCONFIG})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib/${OUTPUTCONFIG})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib/${OUTPUTCONFIG})
    endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)
endif()

# ============================================================================
# Find Required Packages
# ============================================================================

find_package(Threads REQUIRED)

# ============================================================================
# CEF (Chromium Embedded Framework) Configuration
# ============================================================================

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CEFDownload.cmake)

# ============================================================================
# Modern Renderer
# ============================================================================

add_subdirectory(modern_renderer)

# ============================================================================
# Netscape Core Libraries
# ============================================================================

add_subdirectory(nsprpub)
add_subdirectory(xpcom)
add_subdirectory(base)
add_subdirectory(network)
add_subdirectory(modules)

# ============================================================================
# Netscape Application
# ============================================================================

set(NETSCAPE_SOURCES
    cmd/main.cc
    cmd/browser.cc
    cmd/window.cc
)

set(NETSCAPE_HEADERS
    include/nsIBrowser.h
    include/nsIWindow.h
)

# Create main browser executable
add_executable(netscape ${NETSCAPE_SOURCES})

# Windows subsystem
if(WINDOWS)
    set_target_properties(netscape PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# Link dependencies
target_link_libraries(netscape
    PRIVATE
        Threads::Threads
        modern_renderer
        nsprpub
        xpcom
        base
        network
        modules
)

target_include_directories(netscape
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/modern_renderer/include
)

# Windows-specific libraries
if(WINDOWS)
    target_link_libraries(netscape PRIVATE
        user32.lib
        kernel32.lib
        shell32.lib
        ole32.lib
        oleaut32.lib
    )
endif()

# ============================================================================
# Build Options
# ============================================================================

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

option(BUILD_DOCS "Build documentation" ON)
option(USE_STATIC_RUNTIME "Use static C runtime (Windows)" OFF)

# Static C runtime for Windows
if(WINDOWS AND USE_STATIC_RUNTIME)
    foreach(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif()
    endforeach()
endif()

# ============================================================================
# Installation
# ============================================================================

install(TARGETS netscape
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES ${NETSCAPE_HEADERS}
    DESTINATION include
)

if(WINDOWS)
    # Copy CEF DLLs to bin directory
    install(DIRECTORY ${CEF_BINARY_DIR}/bin/
        DESTINATION bin
        FILES_MATCHING PATTERN "*.dll"
    )
endif()

# ============================================================================
# Summary
# ============================================================================

message(STATUS "")
message(STATUS "=== Netscape 5.0 with Modern Blink Renderer ===")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Generator: ${CMAKE_GENERATOR}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Modern Renderer: ENABLED")
message(STATUS "Tests: ${BUILD_TESTS}")
message(STATUS "")

if(WINDOWS)
    message(STATUS "Windows Build Configuration:")
    message(STATUS "  Visual Studio Version: ${MSVC_VERSION}")
    message(STATUS "  Static Runtime: ${USE_STATIC_RUNTIME}")
    message(STATUS "  CEF Binary: ${CEF_BINARY_DIR}")
    message(STATUS "")
endif()

message(STATUS "Build targets:")
message(STATUS "  Build All      - Build everything")
message(STATUS "  netscape       - Build Netscape browser")
message(STATUS "  Run Tests      - Run test suite")
message(STATUS "  INSTALL        - Install binaries")
message(STATUS "")

if(WINDOWS)
    message(STATUS "Visual Studio Instructions:")
    message(STATUS "  1. Open: build/Netscape.sln")
    message(STATUS "  2. Select build configuration (Debug/Release)")
    message(STATUS "  3. Build Solution (Ctrl+Shift+B)")
    message(STATUS "  4. Run: Debug > Start Without Debugging (Ctrl+F5)")
    message(STATUS "")
else()
    message(STATUS "Build instructions:")
    message(STATUS "  make -j$(nproc)    - Build everything")
    message(STATUS "  make netscape      - Build browser only")
    message(STATUS "  make test          - Run tests")
    message(STATUS "  make install       - Install binaries")
    message(STATUS "")
endif()
