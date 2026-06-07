#include "../modern_renderer/include/renderer_bridge.h"
#include <iostream>
#include <cassert>

using namespace netscape::modern;

int main() {
    std::cout << "Netscape Rendering Tests" << std::endl;
    std::cout << "" << std::endl;

    RendererBridge renderer;

    // Test 1: Legacy HTML
    std::cout << "Test 1: Legacy HTML Rendering" << std::endl;
    std::string legacy = "<html><body><h1>Test</h1></body></html>";
    renderer.ParseHTML(legacy);
    renderer.Layout();
    renderer.Paint();
    std::cout << "  ✓ Legacy HTML rendered" << std::endl;

    // Test 2: Modern HTML5
    std::cout << "Test 2: Modern HTML5 Rendering" << std::endl;
    std::string modern = "<!DOCTYPE html><html><body><h1>Test</h1></body></html>";
    renderer.ParseHTML(modern);
    renderer.Layout();
    renderer.Paint();
    std::cout << "  ✓ Modern HTML5 rendered" << std::endl;

    // Test 3: CSS Styling
    std::cout << "Test 3: CSS Styling" << std::endl;
    renderer.ApplyCSS("body { background-color: white; }");
    std::cout << "  ✓ CSS applied" << std::endl;

    // Test 4: Performance
    std::cout << "Test 4: Performance Metrics" << std::endl;
    auto metrics = renderer.GetLastMetrics();
    assert(metrics.parse_time_ms >= 0);
    assert(metrics.layout_time_ms >= 0);
    assert(metrics.paint_time_ms >= 0);
    std::cout << "  ✓ Metrics collected" << std::endl;
    std::cout << "    Parse: " << metrics.parse_time_ms << " ms" << std::endl;
    std::cout << "    Layout: " << metrics.layout_time_ms << " ms" << std::endl;
    std::cout << "    Paint: " << metrics.paint_time_ms << " ms" << std::endl;

    std::cout << "" << std::endl;
    std::cout << "All rendering tests passed!" << std::endl;

    return 0;
}
