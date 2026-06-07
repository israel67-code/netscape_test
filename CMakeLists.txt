cmake_minimum_required(VERSION 3.15)
project(NetscapeBrowser VERSION 5.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compiler flags
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror -fPIC)
    if(APPLE)
        add_compile_options(-fno-common)
    endif()
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find required packages
find_package(Threads REQUIRED)

# Modern Renderer
add_subdirectory(modern_renderer)

# ============================================================================
# Netscape Core Libraries
# ============================================================================

# NSPR (Netscape Portable Runtime)
add_subdirectory(nsprpub)

# XPCOM (Cross Platform Component Object Model)
add_subdirectory(xpcom)

# Base utilities
add_subdirectory(base)

# Network
add_subdirectory(network)

# Modules
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

# Link dependencies
target_link_libraries(netscape
    PRIVATE
        Threads::Threads
        modern_renderer      # Modern Blink Renderer
        nsprpub              # Netscape Portable Runtime
        xpcom                # Component Object Model
        base                 # Base utilities
        network              # Network module
        modules              # Additional modules
)

target_include_directories(netscape
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/modern_renderer/include
)

# ============================================================================
# Build Options
# ============================================================================

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

option(BUILD_DOCS "Build documentation" ON)
if(BUILD_DOCS)
    # Documentation targets
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

# ============================================================================
# Summary
# ============================================================================

message(STATUS "")
message(STATUS "=== Netscape 5.0 with Modern Blink Renderer ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Modern Renderer: ENABLED")
message(STATUS "Tests: ${BUILD_TESTS}")
message(STATUS "")
message(STATUS "Build targets:")
message(STATUS "  make                 - Build everything")
message(STATUS "  make netscape        - Build Netscape browser")
message(STATUS "  make test            - Run tests")
message(STATUS "  make install         - Install binaries")
message(STATUS "")
message(STATUS "After build:")
message(STATUS "  ./bin/netscape       - Run the browser")
message(STATUS "")
