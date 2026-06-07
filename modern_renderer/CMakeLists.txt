# Modern Renderer Windows Build Configuration

cmake_minimum_required(VERSION 3.15)

# Include Windows-specific configuration
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/CommonConfig.cmake)

# Find CEF
if(NOT CEF_FOUND)
    message(FATAL_ERROR "CEF not found. Please ensure CEF_ROOT is set.")
endif()

# ============================================================================
# Modern Renderer Library
# ============================================================================

set(RENDERER_HEADERS
    include/blink_wrapper.h
    include/renderer_bridge.h
    include/dom_adapter.h
    include/css_processor.h
    include/paint_backend.h
    include/cef_client.h
)

set(RENDERER_SOURCES
    src/blink_wrapper.cc
    src/renderer_bridge.cc
    src/dom_adapter.cc
    src/css_processor.cc
    src/paint_backend.cc
    src/cef_client.cc
)

add_library(modern_renderer STATIC ${RENDERER_SOURCES})

target_include_directories(modern_renderer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Windows-specific configuration
if(WINDOWS)
    target_link_libraries(modern_renderer PRIVATE
        user32.lib
        kernel32.lib
        gdi32.lib
        shell32.lib
    )
endif()

# Link CEF
if(CEF_FOUND)
    target_link_libraries(modern_renderer PUBLIC
        libcef
        libcef_dll_wrapper
    )
    target_include_directories(modern_renderer PUBLIC
        ${CEF_ROOT}
    )
endif()

# Compiler flags
if(MSVC)
    target_compile_options(modern_renderer PRIVATE /W4 /WX)
else()
    target_compile_options(modern_renderer PRIVATE -Wall -Wextra -Werror)
endif()

message(STATUS "Modern Renderer configured")
