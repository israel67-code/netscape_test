# Generate Visual Studio Solution and Projects
# This script sets up Visual Studio-specific build configuration

get_cmake_property(_variableNames VARIABLES)

message(STATUS "")
message(STATUS "=== Visual Studio Configuration ===")
message(STATUS "Generator: ${CMAKE_GENERATOR}")
message(STATUS "Platform: ${CMAKE_GENERATOR_PLATFORM}")
message(STATUS "")

# Set Visual Studio-specific properties
if(MSVC)
    # Use static runtime for consistent builds
    if(USE_STATIC_RUNTIME)
        foreach(flag_var 
            CMAKE_CXX_FLAGS_DEBUG 
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_RELEASE)
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endforeach()
    endif()
    
    # Set Windows SDK version
    set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "Windows 10 SDK")
endif()

message(STATUS "Visual Studio Configuration Complete")
