#ifndef MODERN_RENDERER_BLINK_WRAPPER_H_
#define MODERN_RENDERER_BLINK_WRAPPER_H_

#include <string>
#include <memory>
#include <functional>
#include "include/cef_client.h"
#include "include/cef_browser.h"

namespace netscape {
namespace modern {

/**
 * BlinkWrapper: High-level wrapper around Chromium Embedded Framework (CEF)
 * Replaces legacy Netscape rendering engine with modern Blink/WebKit
 */
class BlinkWrapper {
 public:
  BlinkWrapper();
  ~BlinkWrapper();

  // Initialize CEF and Blink engine
  bool Initialize();
  bool Shutdown();

  // Load and render HTML content
  bool LoadHTML(const std::string& html_content);
  bool LoadURL(const std::string& url);

  // Rendering callbacks
  using RenderCallback = std::function<void(const std::string&)>;
  void SetOnRenderComplete(RenderCallback callback);

  // Get rendered output
  std::string GetRenderedHTML();
  CefRefPtr<CefBrowser> GetBrowser() const { return browser_; }

  // CSS and DOM manipulation
  bool InjectCSS(const std::string& css);
  bool EvaluateJavaScript(const std::string& js_code);

  // Rendering options
  void SetViewportSize(int width, int height);
  void SetDevicePixelRatio(float ratio);

 private:
  CefRefPtr<CefBrowser> browser_;
  RenderCallback render_callback_;
  int viewport_width_;
  int viewport_height_;
  float device_pixel_ratio_;
};

}  // namespace modern
}  // namespace netscape

#endif  // MODERN_RENDERER_BLINK_WRAPPER_H_
