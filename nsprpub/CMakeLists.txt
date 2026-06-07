# Stub CMakeLists for nsprpub
# In a real scenario, this would compile the full NSPR library

add_library(nsprpub INTERFACE)

target_include_directories(nsprpub INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# For now, this is a stub. In production, you would:
# 1. Use the existing NSPR build system
# 2. Or create a full CMake wrapper around it
message(STATUS "NSPR (Netscape Portable Runtime) - Stub implementation")
