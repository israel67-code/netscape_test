# CEF (Chromium Embedded Framework) Download and Configuration
# This script handles downloading and setting up CEF for the current platform

include(FetchContent)

set(CEF_VERSION "102.0.0")
set(CEF_BUILD_VERSION "102.0.0+gUUID+chromium-102.0.5005.61")

# Determine platform and architecture
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(CEF_PLATFORM "windows64")
        set(CEF_FILENAME "cef_binary_${CEF_BUILD_VERSION}_windows64.zip")
        set(CEF_URL "https://github.com/chromiumembedded/cef-builds/releases/download/cef_binary_${CEF_BUILD_VERSION}_windows64/cef_binary_${CEF_BUILD_VERSION}_windows64.zip")
    else()
        set(CEF_PLATFORM "windows32")
        set(CEF_FILENAME "cef_binary_${CEF_BUILD_VERSION}_windows32.zip")
        set(CEF_URL "https://github.com/chromiumembedded/cef-builds/releases/download/cef_binary_${CEF_BUILD_VERSION}_windows32/cef_binary_${CEF_BUILD_VERSION}_windows32.zip")
    endif()
elseif(APPLE)
    set(CEF_PLATFORM "macosx64")
    set(CEF_FILENAME "cef_binary_${CEF_BUILD_VERSION}_macosx64.tar.bz2")
    set(CEF_URL "https://github.com/chromiumembedded/cef-builds/releases/download/cef_binary_${CEF_BUILD_VERSION}_macosx64/cef_binary_${CEF_BUILD_VERSION}_macosx64.tar.bz2")
elseif(UNIX AND NOT APPLE)
    set(CEF_PLATFORM "linux64")
    set(CEF_FILENAME "cef_binary_${CEF_BUILD_VERSION}_linux64.tar.bz2")
    set(CEF_URL "https://github.com/chromiumembedded/cef-builds/releases/download/cef_binary_${CEF_BUILD_VERSION}_linux64/cef_binary_${CEF_BUILD_VERSION}_linux64.tar.bz2")
endif()

set(CEF_ROOT "${CMAKE_BINARY_DIR}/deps/cef_binary_${CEF_BUILD_VERSION}_${CEF_PLATFORM}")
set(CEF_BINARY_DIR "${CEF_ROOT}")

message(STATUS "CEF Configuration:")
message(STATUS "  Platform: ${CEF_PLATFORM}")
message(STATUS "  Version: ${CEF_VERSION}")
message(STATUS "  Root: ${CEF_ROOT}")

if(NOT EXISTS "${CEF_ROOT}/CMakeLists.txt")
    message(STATUS "CEF not found. Downloading...")
    message(STATUS "  URL: ${CEF_URL}")
    
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/deps/${CEF_FILENAME}")
        file(DOWNLOAD
            "${CEF_URL}"
            "${CMAKE_BINARY_DIR}/deps/${CEF_FILENAME}"
            STATUS DOWNLOAD_STATUS
            SHOW_PROGRESS
        )
        
        list(GET DOWNLOAD_STATUS 0 DOWNLOAD_RESULT)
        if(NOT DOWNLOAD_RESULT EQUAL 0)
            list(GET DOWNLOAD_STATUS 1 ERROR_MESSAGE)
            message(FATAL_ERROR "Failed to download CEF: ${ERROR_MESSAGE}")
        endif()
    endif()
    
    message(STATUS "Extracting CEF...")
    if(WIN32 AND CEF_FILENAME MATCHES "\.zip$")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xf "${CMAKE_BINARY_DIR}/deps/${CEF_FILENAME}"
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/deps"
        )
    else()
        execute_process(
            COMMAND tar xjf "${CMAKE_BINARY_DIR}/deps/${CEF_FILENAME}"
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/deps"
        )
    endif()
    
    message(STATUS "CEF extraction complete")
else()
    message(STATUS "CEF found at ${CEF_ROOT}")
endif()

# Include CEF's CMakeLists.txt if available
if(EXISTS "${CEF_ROOT}/CMakeLists.txt")
    add_subdirectory(${CEF_ROOT} ${CMAKE_BINARY_DIR}/cef)
    set(CEF_FOUND TRUE)
else()
    message(WARNING "CEF CMakeLists.txt not found")
    set(CEF_FOUND FALSE)
endif()
