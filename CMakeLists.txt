# Netscape 5.0 - CEF-Based Implementation
# Updated to properly use CEF 148.0.10

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
    add_compile_options(/W4 /MP)
    add_compile_options(/std:c++17)
    add_compile_options(/EHsc)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Oi /Ot /GL")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od /RTC1")
else()
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

if(WINDOWS)
    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin/${OUTPUTCONFIG})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib/${OUTPUTCONFIG})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib/${OUTPUTCONFIG})
    endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)
endif()

# ============================================================================
# CEF Configuration
# ============================================================================

if(NOT CEF_ROOT)
    message(FATAL_ERROR "CEF_ROOT must be specified. Use: cmake .. -DCEF_ROOT=<path>")
endif()

if(NOT EXISTS "${CEF_ROOT}/include/cef_version.h")
    message(FATAL_ERROR "CEF not found at ${CEF_ROOT}")
endif()

message(STATUS "CEF Root: ${CEF_ROOT}")

find_package(Threads REQUIRED)

# ============================================================================
# Modern Renderer
# ============================================================================

add_subdirectory(modern_renderer)

# ============================================================================
# Netscape Application
# ============================================================================

set(NETSCAPE_SOURCES
    cmd/main.cc
)

add_executable(netscape ${NETSCAPE_SOURCES})

if(WINDOWS)
    set_target_properties(netscape PROPERTIES WIN32_EXECUTABLE FALSE)
endif()

target_link_libraries(netscape
    PRIVATE
        Threads::Threads
        modern_renderer
)

target_include_directories(netscape
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/modern_renderer/include
        ${CEF_ROOT}
)

if(WINDOWS)
    target_link_libraries(netscape PRIVATE
        user32.lib
        kernel32.lib
        shell32.lib
    )
endif()

# ============================================================================
# Build Summary
# ============================================================================

message(STATUS "")
message(STATUS "=== Netscape 5.0 CEF Build Configuration ===")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Generator: ${CMAKE_GENERATOR}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "CEF Version: 148.0.10+")
message(STATUS "")
message(STATUS "Build target: netscape")
message(STATUS "Output: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "")
