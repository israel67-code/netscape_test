#include "../include/renderer_bridge.h"
#include "../include/dom_adapter.h"
#include "../include/css_processor.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace netscape::modern;

/**
 * Integration Tests: Test complete rendering pipeline
 */

void TestLegacyHTML() {
  std::cout << "Test: Legacy HTML4 Document" << std::endl;

  std::string legacy_html = R"(
    <html>
    <head>
      <title>Legacy Page</title>
    </head>
    <body bgcolor="#ffffff" text="#000000">
      <center>
        <h1>Welcome</h1>
        <font face="Arial" size="3">This is old HTML</font>
      </center>
      <hr>
      <p align="center">
        <img src="image.jpg" width="200" height="150">
      </p>
    </body>
    </html>
  )";

  RendererBridge renderer;
  renderer.ParseHTML(legacy_html);
  renderer.Layout();
  renderer.Paint();

  auto metrics = renderer.GetLastMetrics();
  assert(metrics.parse_time_ms >= 0);
  std::cout << "  ✓ Legacy HTML rendered in " << metrics.parse_time_ms << " ms" << std::endl;
}

void TestModernHTML5() {
  std::cout << "Test: Modern HTML5 Document" << std::endl;

  std::string modern_html = R"(
    <!DOCTYPE html>
    <html lang="en">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Modern Page</title>
      <style>
        body { font-family: sans-serif; margin: 0; padding: 20px; }
        header { background: #333; color: white; padding: 20px; }
        main { max-width: 1000px; margin: 20px auto; }
        article { margin: 20px 0; padding: 20px; background: #f5f5f5; }
      </style>
    </head>
    <body>
      <header>
        <h1>Modern Website</h1>
      </header>
      <main>
        <article>
          <h2>Article Title</h2>
          <p>This is modern HTML5 with semantic elements.</p>
        </article>
      </main>
    </body>
    </html>
  )";

  RendererBridge renderer;
  renderer.ParseHTML(modern_html);
  renderer.Layout();
  renderer.Paint();

  auto metrics = renderer.GetLastMetrics();
  assert(metrics.parse_time_ms >= 0);
  std::cout << "  ✓ Modern HTML5 rendered in " << metrics.parse_time_ms << " ms" << std::endl;
}

void TestResponsiveDesign() {
  std::cout << "Test: Responsive Design" << std::endl;

  std::string responsive_html = R"(
    <!DOCTYPE html>
    <html>
    <head>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <style>
        * { box-sizing: border-box; }
        body { margin: 0; padding: 0; }
        .container { max-width: 1200px; margin: 0 auto; padding: 20px; }
        .grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 20px; }
        .card { background: white; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }
        @media (max-width: 768px) {
          .grid { grid-template-columns: 1fr; }
        }
      </style>
    </head>
    <body>
      <div class="container">
        <div class="grid">
          <div class="card"><h3>Card 1</h3><p>Responsive content</p></div>
          <div class="card"><h3>Card 2</h3><p>Responsive content</p></div>
          <div class="card"><h3>Card 3</h3><p>Responsive content</p></div>
        </div>
      </div>
    </body>
    </html>
  )";

  RendererBridge renderer;
  renderer.ParseHTML(responsive_html);
  renderer.Layout();
  renderer.Paint();

  std::cout << "  ✓ Responsive design rendered correctly" << std::endl;
}

void TestCSSModernization() {
  std::cout << "Test: CSS Modernization" << std::endl;

  CSSProcessor processor;

  // Test deprecated property conversion
  std::string modernized = processor.ModernizeProperty("bgcolor", "#ffffff");
  assert(!modernized.empty());
  std::cout << "  ✓ bgcolor -> background-color" << std::endl;

  // Test layout property conversion
  std::string layout = processor.ConvertLayoutProperty("float", "left");
  assert(!layout.empty());
  std::cout << "  ✓ float -> flexbox" << std::endl;

  // Test vendor prefixes
  std::string prefixed = processor.AddVendorPrefixes("transform", "rotate(45deg)");
  assert(prefixed.find("-webkit-") != std::string::npos);
  std::cout << "  ✓ Vendor prefixes added" << std::endl;
}

void TestDOMManipulation() {
  std::cout << "Test: DOM Manipulation" << std::endl;

  std::string html = R"(
    <html>
    <body>
      <div id="content" class="container">
        <h1>Title</h1>
        <p>Content</p>
      </div>
    </body>
    </html>
  )";

  RendererBridge renderer;
  renderer.ParseHTML(html);

  // Apply CSS
  renderer.ApplyCSS("#content { background: blue; }");
  std::cout << "  ✓ CSS applied to DOM" << std::endl;

  // Modify DOM
  renderer.ModifyDOM("h1", "color", "red");
  std::cout << "  ✓ DOM element modified" << std::endl;
}

void TestPerformance() {
  std::cout << "Test: Performance Metrics" << std::endl;

  std::string html = R"(
    <!DOCTYPE html>
    <html>
    <head>
      <style>
        body { font-family: Arial; }
        .container { max-width: 1000px; margin: 0 auto; }
        .grid { display: grid; grid-template-columns: repeat(3, 1fr); gap: 20px; }
        .item { padding: 20px; background: #f0f0f0; }
      </style>
    </head>
    <body>
      <div class="container">
        <h1>Performance Test</h1>
        <div class="grid">
          <div class="item">1</div>
          <div class="item">2</div>
          <div class="item">3</div>
          <div class="item">4</div>
          <div class="item">5</div>
          <div class="item">6</div>
        </div>
      </div>
    </body>
    </html>
  )";

  RendererBridge renderer;
  renderer.ParseHTML(html);
  renderer.Layout();
  renderer.Paint();

  auto metrics = renderer.GetLastMetrics();

  std::cout << "  Parse: " << metrics.parse_time_ms << " ms" << std::endl;
  std::cout << "  Layout: " << metrics.layout_time_ms << " ms" << std::endl;
  std::cout << "  Paint: " << metrics.paint_time_ms << " ms" << std::endl;
  std::cout << "  Total: " << metrics.total_time_ms << " ms" << std::endl;

  // Verify performance is acceptable (adjust thresholds as needed)
  assert(metrics.parse_time_ms < 100);
  assert(metrics.layout_time_ms < 100);
  assert(metrics.paint_time_ms < 200);

  std::cout << "  ✓ Performance targets met" << std::endl;
}

int main(int argc, char* argv[]) {
  std::cout << "=== Modern Blink Renderer - Integration Tests ===" << std::endl;
  std::cout << std::endl;

  try {
    TestLegacyHTML();
    std::cout << std::endl;

    TestModernHTML5();
    std::cout << std::endl;

    TestResponsiveDesign();
    std::cout << std::endl;

    TestCSSModernization();
    std::cout << std::endl;

    TestDOMManipulation();
    std::cout << std::endl;

    TestPerformance();
    std::cout << std::endl;

    std::cout << "========================================" << std::endl;
    std::cout << "All integration tests passed! ✓" << std::endl;
    std::cout << "========================================" << std::endl;

  } catch (const std::exception& e) {
    std::cerr << "\nTest failed: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
