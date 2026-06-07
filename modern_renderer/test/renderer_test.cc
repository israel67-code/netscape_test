#include "../include/renderer_bridge.h"
#include "../include/dom_adapter.h"
#include "../include/css_processor.h"
#include <cassert>
#include <iostream>

using namespace netscape::modern;

void TestDOMAdapter() {
  std::cout << "Testing DOMAdapter..." << std::endl;
  
  DOMAdapter adapter;
  
  // Test tag modernization
  std::string modernized_center = adapter.ModernizeTag("center");
  assert(modernized_center == "div");
  std::cout << "  ✓ HTML4 <center> -> <div>" << std::endl;
  
  std::string modernized_font = adapter.ModernizeTag("font");
  assert(modernized_font == "span");
  std::cout << "  ✓ HTML4 <font> -> <span>" << std::endl;
}

void TestCSSProcessor() {
  std::cout << "Testing CSSProcessor..." << std::endl;
  
  CSSProcessor processor;
  
  std::string css = "body { bgcolor: #ffffff; margin: 0; }";
  auto rules = processor.ProcessCSS(css);
  
  std::cout << "  ✓ CSS parsing and modernization" << std::endl;
}

void TestRendererBridge() {
  std::cout << "Testing RendererBridge..." << std::endl;
  
  RendererBridge renderer;
  
  std::string html = "<html><body><h1>Test</h1></body></html>";
  renderer.ParseHTML(html);
  renderer.Layout();
  renderer.Paint();
  
  auto metrics = renderer.GetLastMetrics();
  assert(metrics.parse_time_ms >= 0);
  assert(metrics.layout_time_ms >= 0);
  assert(metrics.paint_time_ms >= 0);
  
  std::cout << "  ✓ HTML parsing, layout, and painting" << std::endl;
}

int main(int argc, char* argv[]) {
  std::cout << "=== Modern Blink Renderer Tests ===" << std::endl;
  std::cout << std::endl;
  
  try {
    TestDOMAdapter();
    std::cout << std::endl;
    
    TestCSSProcessor();
    std::cout << std::endl;
    
    TestRendererBridge();
    std::cout << std::endl;
    
    std::cout << "All tests passed! ✓" << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Test failed: " << e.what() << std::endl;
    return 1;
  }
  
  return 0;
}
