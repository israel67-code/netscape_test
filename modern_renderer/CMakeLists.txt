cmake_minimum_required(VERSION 3.15)
project(ModernBlinkRenderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(CEF REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Skia REQUIRED)

# Source files
set(SOURCES
  src/blink_wrapper.cc
  src/renderer_bridge.cc
  src/dom_adapter.cc
  src/css_processor.cc
  src/paint_backend.cc
  src/main.cc
)

set(HEADERS
  include/blink_wrapper.h
  include/renderer_bridge.h
  include/dom_adapter.h
  include/css_processor.h
  include/paint_backend.h
)

# Create library
add_library(modern_renderer STATIC ${SOURCES})

# Link dependencies
target_link_libraries(modern_renderer
  PRIVATE
    CEF::cef_wrapper
    CEF::cef_dll_wrapper
    OpenGL::OpenGL
    Skia::Skia
)

target_include_directories(modern_renderer PUBLIC include)

# Executable for testing
add_executable(renderer_test test/renderer_test.cc)
target_link_libraries(renderer_test modern_renderer)
