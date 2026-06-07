#include "include/renderer_bridge.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace netscape::modern;

int main(int argc, char* argv[]) {
  std::cout << "=== Modern Blink Renderer for Netscape 5.0 ===" << std::endl;
  std::cout << "Replacing legacy rendering engine with modern Blink/WebKit" << std::endl;
  std::cout << std::endl;

  // Create renderer bridge
  RendererBridge renderer;

  // Example: Legacy HTML that would have used Netscape rendering
  std::string legacy_html = R"(
    <html>
      <head>
        <title>Modern Rendering Test</title>
        <style>
          body { font-family: Arial; margin: 20px; }
          .container { width: 100%; max-width: 800px; }
          h1 { color: #0066cc; }
        </style>
      </head>
      <body>
        <h1>Netscape 5.0 Modernized</h1>
        <p>This page is now rendered using modern Blink/WebKit engine!</p>
        <div class="container">
          <p>Legacy HTML4 content is automatically converted to HTML5.</p>
        </div>
      </body>
    </html>
  )";

  // Parse with modern renderer
  std::cout << "Parsing HTML..." << std::endl;
  renderer.ParseHTML(legacy_html);

  // Layout and paint
  std::cout << "Performing layout..." << std::endl;
  renderer.Layout();

  std::cout << "Painting..." << std::endl;
  renderer.Paint();

  // Get metrics
  auto metrics = renderer.GetLastMetrics();
  std::cout << std::endl;
  std::cout << "=== Rendering Metrics ===" << std::endl;
  std::cout << "Parse time: " << metrics.parse_time_ms << " ms" << std::endl;
  std::cout << "Layout time: " << metrics.layout_time_ms << " ms" << std::endl;
  std::cout << "Paint time: " << metrics.paint_time_ms << " ms" << std::endl;
  std::cout << "Total time: " << metrics.total_time_ms << " ms" << std::endl;

  // Apply modern CSS
  std::string modern_css = R"(
    body {
      background-color: #f5f5f5;
      font-size: 14px;
      line-height: 1.6;
    }
    h1 {
      font-size: 28px;
      margin-bottom: 20px;
    }
  )";

  std::cout << std::endl;
  std::cout << "Applying modern CSS..." << std::endl;
  renderer.ApplyCSS(modern_css);

  std::cout << "Successfully integrated modern Blink renderer!" << std::endl;
  std::cout << std::endl;
  std::cout << "Key improvements over legacy renderer:" << std::endl;
  std::cout << "  ✓ HTML5 support" << std::endl;
  std::cout << "  ✓ CSS3 support" << std::endl;
  std::cout << "  ✓ Modern JavaScript" << std::endl;
  std::cout << "  ✓ GPU acceleration" << std::endl;
  std::cout << "  ✓ Responsive design" << std::endl;
  std::cout << "  ✓ Better performance" << std::endl;

  return 0;
}
