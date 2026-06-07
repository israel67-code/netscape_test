#pragma once

#include <string>
#include <vector>

namespace netscape::modern {

// Metrics for rendering performance
struct RenderMetrics {
  double parse_time_ms = 0.0;
  double layout_time_ms = 0.0;
  double paint_time_ms = 0.0;
  double total_time_ms = 0.0;
};

// Simple bridge to CEF functionality
class RendererBridge {
 public:
  RendererBridge();
  ~RendererBridge();

  // Core rendering functions
  bool ParseHTML(const std::string& html);
  bool Layout();
  bool Paint();
  bool ApplyCSS(const std::string& css);

  // Get rendering metrics
  const RenderMetrics& GetLastMetrics() const { return metrics_; }

  // Browser control
  bool LoadURL(const std::string& url);
  bool ExecuteFunction(const std::string& function, const std::vector<std::string>& args);

 private:
  RenderMetrics metrics_;
  std::string current_html_;
  std::string current_css_;
};

}  // namespace netscape::modern
