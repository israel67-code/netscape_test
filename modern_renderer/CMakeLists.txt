# Modern Renderer - CEF-Based Implementation

cmake_minimum_required(VERSION 3.15)

# Include Windows CEF configuration
if(WIN32)
    include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/CEFWindows.cmake)
endif()

# ============================================================================
# Modern Renderer Library
# ============================================================================

set(RENDERER_HEADERS
    include/netscape_app.h
    include/simple_client.h
    include/renderer_bridge.h
)

set(RENDERER_SOURCES
    src/netscape_app.cc
    src/simple_client.cc
    src/renderer_bridge.cc
)

add_library(modern_renderer STATIC ${RENDERER_SOURCES})

target_include_directories(modern_renderer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CEF_ROOT}
)

# Link CEF
if(CEF_ROOT)
    # Link CEF libraries
    target_link_directories(modern_renderer PRIVATE
        ${CEF_ROOT}/Release
        ${CEF_ROOT}/libcef_dll_wrapper/Release
    )
    
    target_link_libraries(modern_renderer PUBLIC
        libcef
        libcef_dll_wrapper
    )
    
    # Windows system libraries
    if(WIN32)
        target_link_libraries(modern_renderer PRIVATE
            user32.lib
            kernel32.lib
            gdi32.lib
            shell32.lib
            ole32.lib
            oleaut32.lib
            shlwapi.lib
            comctl32.lib
        )
    endif()
else()
    message(FATAL_ERROR "CEF_ROOT not set. Please specify CEF location.")
endif()

# Compiler flags
if(MSVC)
    target_compile_options(modern_renderer PRIVATE /W4)
    # Define Windows macros
    target_compile_definitions(modern_renderer PRIVATE
        WIN32
        _WINDOWS
        _CRT_SECURE_NO_WARNINGS
    )
else()
    target_compile_options(modern_renderer PRIVATE -Wall -Wextra)
endif()

message(STATUS "Modern Renderer (CEF-based) configured")
message(STATUS "  CEF Root: ${CEF_ROOT}")
message(STATUS "  Includes: ${CMAKE_CURRENT_SOURCE_DIR}/include")
