#include "include/renderer_bridge.h"
#include "include/blink_wrapper.h"
#include "include/dom_adapter.h"
#include "include/css_processor.h"
#include <chrono>
#include <iostream>

namespace netscape {
namespace modern {

class RendererBridge::Impl {
 public:
  Impl() : blink_wrapper_(std::make_unique<BlinkWrapper>()),
           dom_adapter_(std::make_unique<DOMAdapter>()),
           css_processor_(std::make_unique<CSSProcessor>()) {
    blink_wrapper_->Initialize();
  }

  ~Impl() {
    blink_wrapper_->Shutdown();
  }

  std::unique_ptr<BlinkWrapper> blink_wrapper_;
  std::unique_ptr<DOMAdapter> dom_adapter_;
  std::unique_ptr<CSSProcessor> css_processor_;
};

RendererBridge::RendererBridge()
    : impl_(std::make_unique<Impl>()), legacy_callback_(nullptr) {}

RendererBridge::~RendererBridge() {}

void RendererBridge::ParseHTML(const std::string& html) {
  auto start = std::chrono::high_resolution_clock::now();
  
  // Convert legacy HTML to modern HTML5
  auto dom_tree = impl_->dom_adapter_->ParseHTML(html);
  std::string modern_html = impl_->dom_adapter_->ToHTML5(dom_tree);
  
  // Load into Blink renderer
  impl_->blink_wrapper_->LoadHTML(modern_html);

  auto end = std::chrono::high_resolution_clock::now();
  metrics_.parse_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
}

void RendererBridge::Layout() {
  auto start = std::chrono::high_resolution_clock::now();
  
  // Blink handles layout internally
  // This is maintained for API compatibility
  
  auto end = std::chrono::high_resolution_clock::now();
  metrics_.layout_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
}

void RendererBridge::Paint() {
  auto start = std::chrono::high_resolution_clock::now();
  
  // Trigger paint operation in Blink
  impl_->blink_wrapper_->GetBrowser()->GetHost()->Invalidate(PET_VIEW);
  
  auto end = std::chrono::high_resolution_clock::now();
  metrics_.paint_time_ms = std::chrono::duration<double, std::milli>(end - start).count();
}

void RendererBridge::Reflow() {
  // Request reflow in Blink
  ParseHTML(impl_->blink_wrapper_->GetRenderedHTML());
}

void RendererBridge::RenderToString(std::string& output) {
  output = impl_->blink_wrapper_->GetRenderedHTML();
}

void RendererBridge::RenderToFile(const std::string& filepath) {
  std::string html = impl_->blink_wrapper_->GetRenderedHTML();
  // Write to file
}

void RendererBridge::RenderToPNG(const std::string& filepath) {
  // Render to PNG using paint backend
}

void RendererBridge::SetRenderCallback(RenderCallback callback) {
  legacy_callback_ = callback;
}

void RendererBridge::ApplyCSS(const std::string& css_rules) {
  impl_->blink_wrapper_->InjectCSS(css_rules);
}

void RendererBridge::ModifyDOM(const std::string& selector, const std::string& property, const std::string& value) {
  std::string js = "document.querySelectorAll('" + selector + "').forEach(el => {";
  js += "el.style['" + property + "'] = '" + value + "';})";
  impl_->blink_wrapper_->EvaluateJavaScript(js);
}

}  // namespace modern
}  // namespace netscape
