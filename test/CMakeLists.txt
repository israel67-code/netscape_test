cmake_minimum_required(VERSION 3.15)
project(NetscapeTests)

enable_testing()

# Test executable
add_executable(netscape_test
    test_browser.cc
    test_rendering.cc
)

target_link_libraries(netscape_test
    PRIVATE
        modern_renderer
        nsprpub
        xpcom
)

target_include_directories(netscape_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}/../modern_renderer/include
)

add_test(NAME NetscapeTests COMMAND netscape_test)
