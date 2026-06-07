# Cross-Platform CMake Configuration
# Shared configuration for all platforms

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# ============================================================================
# Common Compiler Flags
# ============================================================================

if(NOT MSVC)
    # GCC/Clang common flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")
endif()

# ============================================================================
# Architecture Detection
# ============================================================================

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCHITECTURE "x64")
    message(STATUS "Architecture: 64-bit")
else()
    set(ARCHITECTURE "x86")
    message(STATUS "Architecture: 32-bit")
endif()
