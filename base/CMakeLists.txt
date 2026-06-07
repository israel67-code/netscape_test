# Stub CMakeLists for base utilities

add_library(base INTERFACE)

target_include_directories(base INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(base INTERFACE xpcom)

message(STATUS "Base utilities - Stub implementation")
