#ifndef MODERN_RENDERER_BRIDGE_H_
#define MODERN_RENDERER_BRIDGE_H_

#include <string>
#include <memory>
#include <vector>

namespace netscape {
namespace modern {

/**
 * RendererBridge: Adapter between legacy Netscape rendering API and modern Blink
 * 
 * This class maintains backward compatibility while routing all rendering
 * operations through the modern Blink/WebKit engine instead of the legacy
 * Netscape rendering pipeline.
 */
class RendererBridge {
 public:
  RendererBridge();
  ~RendererBridge();

  // Legacy Netscape API (mapping to modern renderer)
  typedef void (*RenderCallback)(const char* html_output);
  
  void ParseHTML(const std::string& html);
  void Layout();
  void Paint();
  void Reflow();
  
  // Modern API
  void RenderToString(std::string& output);
  void RenderToFile(const std::string& filepath);
  void RenderToPNG(const std::string& filepath);

  // Register callback for legacy code
  void SetRenderCallback(RenderCallback callback);

  // Style and DOM manipulation
  void ApplyCSS(const std::string& css_rules);
  void ModifyDOM(const std::string& selector, const std::string& property, const std::string& value);

  // Performance metrics
  struct RenderMetrics {
    double parse_time_ms;
    double layout_time_ms;
    double paint_time_ms;
    double total_time_ms;
  };
  RenderMetrics GetLastMetrics() const { return metrics_; }

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
  RenderCallback legacy_callback_;
  RenderMetrics metrics_;
};

}  // namespace modern
}  // namespace netscape

#endif  // MODERN_RENDERER_BRIDGE_H_
