cmake_minimum_required(VERSION 3.15)

# Stub for Windows-specific CEF wrapper configuration

if(WIN32)
    message(STATUS "Configuring CEF for Windows...")
    
    # Ensure CEF_ROOT is set
    if(NOT CEF_ROOT)
        message(FATAL_ERROR "CEF_ROOT must be set")
    endif()
    
    # Find CEF library
    find_library(CEF_LIB libcef HINTS "${CEF_ROOT}/Release")
    find_library(CEF_DLL_WRAPPER cef_dll_wrapper HINTS "${CEF_ROOT}/libcef_dll_wrapper/Release")
    
    if(NOT CEF_LIB)
        message(WARNING "libcef.lib not found in ${CEF_ROOT}/Release")
    endif()
    
    if(NOT CEF_DLL_WRAPPER)
        message(WARNING "cef_dll_wrapper.lib not found")
    endif()
    
    message(STATUS "CEF configured for Windows")
endif()
