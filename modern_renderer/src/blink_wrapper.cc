#include "include/blink_wrapper.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"
#include <iostream>

namespace netscape {
namespace modern {

BlinkWrapper::BlinkWrapper()
    : viewport_width_(1024),
      viewport_height_(768),
      device_pixel_ratio_(1.0f) {}

BlinkWrapper::~BlinkWrapper() {}

bool BlinkWrapper::Initialize() {
  // Initialize CEF (Chromium Embedded Framework)
  CefSettings settings;
  settings.no_sandbox = true;
  settings.multi_threaded_message_loop = true;

  if (!CefInitialize(settings)) {
    std::cerr << "Failed to initialize CEF" << std::endl;
    return false;
  }

  // Create browser instance
  CefBrowserSettings browser_settings;
  browser_settings.web_security_disabled = true;

  // Create main browser window
  CefWindowInfo window_info;
  window_info.SetAsChild(NULL, 0, 0, viewport_width_, viewport_height_);

  std::cout << "Blink wrapper initialized successfully" << std::endl;
  return true;
}

bool BlinkWrapper::Shutdown() {
  if (browser_.get()) {
    browser_->GetHost()->CloseBrowser(true);
  }
  CefShutdown();
  return true;
}

bool BlinkWrapper::LoadHTML(const std::string& html_content) {
  if (!browser_.get()) {
    std::cerr << "Browser not initialized" << std::endl;
    return false;
  }

  // Load HTML into Blink renderer
  std::string data_url = "data:text/html," + html_content;
  browser_->GetMainFrame()->LoadURL(data_url);
  return true;
}

bool BlinkWrapper::LoadURL(const std::string& url) {
  if (!browser_.get()) return false;
  browser_->GetMainFrame()->LoadURL(url);
  return true;
}

void BlinkWrapper::SetOnRenderComplete(RenderCallback callback) {
  render_callback_ = callback;
}

std::string BlinkWrapper::GetRenderedHTML() {
  // Get rendered output from Blink
  // This would typically involve executing JavaScript to get the DOM
  return "<html><!-- rendered by Blink --></html>";
}

bool BlinkWrapper::InjectCSS(const std::string& css) {
  if (!browser_.get()) return false;
  
  std::string script = "var style = document.createElement('style'); "
                      "style.textContent = " + css + "; "
                      "document.head.appendChild(style);";
  
  browser_->GetMainFrame()->ExecuteFunction(script, nullptr, 0);
  return true;
}

bool BlinkWrapper::EvaluateJavaScript(const std::string& js_code) {
  if (!browser_.get()) return false;
  browser_->GetMainFrame()->ExecuteFunction(js_code, nullptr, 0);
  return true;
}

void BlinkWrapper::SetViewportSize(int width, int height) {
  viewport_width_ = width;
  viewport_height_ = height;
}

void BlinkWrapper::SetDevicePixelRatio(float ratio) {
  device_pixel_ratio_ = ratio;
}

}  // namespace modern
}  // namespace netscape
