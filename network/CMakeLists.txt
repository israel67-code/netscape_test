# Stub CMakeLists for network

add_library(network INTERFACE)

target_include_directories(network INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(network INTERFACE base)

message(STATUS "Network module - Stub implementation")
