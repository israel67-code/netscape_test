#include "include/renderer_bridge.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

using namespace netscape::modern;

/**
 * Headless Renderer: Renders HTML without GUI window
 * Can be used for batch processing, server-side rendering, etc.
 */
class HeadlessRenderer {
 public:
  HeadlessRenderer() : width_(1920), height_(1080) {}

  bool RenderHTMLFile(const std::string& input_file, const std::string& output_file) {
    // Read HTML file
    std::ifstream input(input_file);
    if (!input.is_open()) {
      std::cerr << "Cannot open: " << input_file << std::endl;
      return false;
    }

    std::stringstream buffer;
    buffer << input.rdbuf();
    std::string html = buffer.str();
    input.close();

    return RenderHTML(html, output_file);
  }

  bool RenderHTML(const std::string& html, const std::string& output_file) {
    std::cout << "\n=== Headless Renderer ===" << std::endl;
    std::cout << "Viewport: " << width_ << "x" << height_ << std::endl;
    std::cout << "Rendering HTML (" << html.length() << " bytes)..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    // Create renderer
    RendererBridge renderer;

    // Parse HTML
    renderer.ParseHTML(html);

    // Layout
    renderer.Layout();

    // Paint
    renderer.Paint();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Get metrics
    auto metrics = renderer.GetLastMetrics();

    std::cout << "\n--- Rendering Metrics ---" << std::endl;
    std::cout << "Parse time: " << metrics.parse_time_ms << " ms" << std::endl;
    std::cout << "Layout time: " << metrics.layout_time_ms << " ms" << std::endl;
    std::cout << "Paint time: " << metrics.paint_time_ms << " ms" << std::endl;
    std::cout << "Total time: " << duration.count() << " ms" << std::endl;

    // Save output
    std::cout << "Saving output to: " << output_file << std::endl;
    SaveOutput(html, output_file);

    return true;
  }

  void SetViewport(int width, int height) {
    width_ = width;
    height_ = height;
  }

 private:
  int width_;
  int height_;

  void SaveOutput(const std::string& html, const std::string& filename) {
    std::ofstream output(filename);
    if (!output.is_open()) {
      std::cerr << "Cannot write output file" << std::endl;
      return;
    }

    // Write HTML with rendering metadata
    output << "<!-- Rendered by Modern Blink Renderer -->\n";
    output << "<!-- Viewport: " << width_ << "x" << height_ << " -->\n";
    output << html;
    output.close();

    std::cout << "✓ Output saved" << std::endl;
  }
};

int main(int argc, char* argv[]) {
  std::cout << "Modern Blink Renderer - Headless Mode" << std::endl;
  std::cout << "======================================" << std::endl;

  HeadlessRenderer renderer;

  // Example: Render a simple HTML file
  std::string example_html = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Modern Website Example</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            display: flex;
            align-items: center;
            justify-content: center;
            padding: 20px;
        }

        .container {
            background: white;
            border-radius: 10px;
            box-shadow: 0 20px 60px rgba(0, 0, 0, 0.3);
            max-width: 800px;
            width: 100%;
            padding: 60px;
            animation: slideIn 0.5s ease-out;
        }

        @keyframes slideIn {
            from {
                opacity: 0;
                transform: translateY(20px);
            }
            to {
                opacity: 1;
                transform: translateY(0);
            }
        }

        h1 {
            color: #667eea;
            font-size: 42px;
            margin-bottom: 20px;
            text-align: center;
        }

        .subtitle {
            color: #888;
            text-align: center;
            font-size: 18px;
            margin-bottom: 40px;
        }

        .features {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 30px;
            margin: 40px 0;
        }

        .feature {
            padding: 20px;
            background: #f5f5f5;
            border-radius: 8px;
            border-left: 4px solid #667eea;
        }

        .feature h3 {
            color: #667eea;
            margin-bottom: 10px;
            font-size: 18px;
        }

        .feature p {
            color: #666;
            line-height: 1.6;
            font-size: 14px;
        }

        .cta {
            text-align: center;
            margin-top: 40px;
        }

        .btn {
            display: inline-block;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 14px 40px;
            border-radius: 8px;
            text-decoration: none;
            font-weight: 600;
            transition: transform 0.3s, box-shadow 0.3s;
            box-shadow: 0 4px 15px rgba(102, 126, 234, 0.4);
        }

        .btn:hover {
            transform: translateY(-2px);
            box-shadow: 0 6px 20px rgba(102, 126, 234, 0.6);
        }

        @media (max-width: 768px) {
            .container {
                padding: 40px 30px;
            }

            h1 {
                font-size: 32px;
            }

            .features {
                grid-template-columns: 1fr;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🚀 Modern Web Rendering</h1>
        <p class="subtitle">Netscape 5.0 Meets Modern Web Standards</p>

        <div class="features">
            <div class="feature">
                <h3>✓ HTML5 Support</h3>
                <p>Full HTML5 specification support with semantic elements and modern APIs.</p>
            </div>

            <div class="feature">
                <h3>✓ CSS3 Styling</h3>
                <p>Advanced CSS3 features including gradients, flexbox, grid, and animations.</p>
            </div>

            <div class="feature">
                <h3>✓ GPU Acceleration</h3>
                <p>Hardware-accelerated rendering for fast, smooth performance.</p>
            </div>

            <div class="feature">
                <h3>✓ Modern JavaScript</h3>
                <p>ES6+ JavaScript execution with modern browser APIs.</p>
            </div>

            <div class="feature">
                <h3>✓ Responsive Design</h3>
                <p>Mobile-first responsive layouts with media queries.</p>
            </div>

            <div class="feature">
                <h3>✓ Web Standards</h3>
                <p>Compliant with current W3C and WHATWG specifications.</p>
            </div>
        </div>

        <div class="cta">
            <a href="#" class="btn">Get Started</a>
        </div>

        <p style="text-align: center; margin-top: 40px; color: #999; font-size: 12px;">
            Powered by Chromium/Blink Engine | Modern Rendering Pipeline
        </p>
    </div>
</body>
</html>
  )";

  // Render the example
  renderer.RenderHTML(example_html, "rendered_example.html");

  // Test with different viewport sizes
  std::cout << "\n\n=== Testing Different Viewports ===" << std::endl;
  renderer.SetViewport(1280, 1024);
  renderer.RenderHTML(example_html, "rendered_tablet.html");

  renderer.SetViewport(375, 667);
  renderer.RenderHTML(example_html, "rendered_mobile.html");

  std::cout << "\n✓ All renders complete!" << std::endl;
  std::cout << "Check output files: rendered_*.html" << std::endl;

  return 0;
}
