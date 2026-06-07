#ifndef MODERN_RENDERER_CSS_PROCESSOR_H_
#define MODERN_RENDERER_CSS_PROCESSOR_H_

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace netscape {
namespace modern {

/**
 * CSSProcessor: Converts legacy CSS to modern CSS3
 * 
 * Handles:
 * - CSS2 → CSS3 property mapping
 * - Vendor prefix normalization
 * - Layout fallbacks (floats → flexbox/grid)
 * - Responsive design upgrades
 */
class CSSProcessor {
 public:
  struct StyleRule {
    std::string selector;
    std::map<std::string, std::string> properties;
    std::string media_query;
  };

  CSSProcessor();
  ~CSSProcessor();

  // Parse legacy CSS and convert to modern
  std::vector<StyleRule> ProcessCSS(const std::string& css);
  
  // Modernize individual properties
  std::string ModernizeProperty(const std::string& property, const std::string& value);
  
  // Add vendor prefixes and fallbacks
  std::string AddVendorPrefixes(const std::string& property, const std::string& value);
  
  // Convert table-based layouts to flexbox
  std::string ConvertLayoutProperty(const std::string& property, const std::string& value);
  
  // Generate modern CSS output
  std::string ToCSS3(const std::vector<StyleRule>& rules);

  // Add responsive design breakpoints
  void AddResponsiveBreakpoints(const std::vector<int>& breakpoints);

 private:
  std::vector<int> breakpoints_;
  
  bool IsDeprecatedProperty(const std::string& property) const;
  std::string GetModernReplacement(const std::string& legacy_property) const;
};

}  // namespace modern
}  // namespace netscape

#endif  // MODERN_RENDERER_CSS_PROCESSOR_H_
