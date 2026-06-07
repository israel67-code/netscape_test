#include <iostream>
#include "../modern_renderer/include/renderer_bridge.h"

using namespace netscape::modern;

/**
 * Netscape 5.0 Browser - Main Application
 * Now powered by Modern Blink Renderer
 */

int main(int argc, char* argv[]) {
    std::cout << "=================================" << std::endl;
    std::cout << "Netscape 5.0 Browser" << std::endl;
    std::cout << "Powered by Modern Blink Renderer" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << std::endl;

    // Initialize Netscape application
    std::cout << "Initializing Netscape Browser..." << std::endl;

    // Create renderer
    RendererBridge renderer;
    std::cout << "Modern Blink Renderer initialized" << std::endl;

    // Example: Load and render a page
    std::string html = R"(
        <!DOCTYPE html>
        <html>
        <head>
            <title>Netscape 5.0 with Modern Renderer</title>
            <style>
                body {
                    font-family: Arial, sans-serif;
                    margin: 40px;
                    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
                    min-height: 100vh;
                    display: flex;
                    align-items: center;
                    justify-content: center;
                }
                .container {
                    background: white;
                    padding: 40px;
                    border-radius: 10px;
                    box-shadow: 0 20px 60px rgba(0,0,0,0.3);
                    max-width: 600px;
                }
                h1 { color: #667eea; }
                p { color: #666; line-height: 1.6; }
            </style>
        </head>
        <body>
            <div class="container">
                <h1>Netscape 5.0 Modernized</h1>
                <p>This browser now runs on the modern Blink rendering engine!</p>
                <p>Features:</p>
                <ul>
                    <li>HTML5 support</li>
                    <li>CSS3 styling</li>
                    <li>Modern JavaScript</li>
                    <li>GPU acceleration</li>
                </ul>
            </div>
        </body>
        </html>
    )";

    std::cout << "\nRendering example page..." << std::endl;
    renderer.ParseHTML(html);
    renderer.Layout();
    renderer.Paint();

    auto metrics = renderer.GetLastMetrics();
    std::cout << "\nRendering completed!" << std::endl;
    std::cout << "Parse time: " << metrics.parse_time_ms << " ms" << std::endl;
    std::cout << "Layout time: " << metrics.layout_time_ms << " ms" << std::endl;
    std::cout << "Paint time: " << metrics.paint_time_ms << " ms" << std::endl;
    std::cout << "Total time: " << metrics.total_time_ms << " ms" << std::endl;

    std::cout << "\nNetscape Browser running successfully!" << std::endl;
    std::cout << "Modern rendering pipeline active." << std::endl;

    return 0;
}
