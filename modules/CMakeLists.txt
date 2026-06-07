# Stub CMakeLists for modules

add_library(modules INTERFACE)

target_include_directories(modules INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(modules INTERFACE network)

message(STATUS "Modules - Stub implementation")
