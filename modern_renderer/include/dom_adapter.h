#ifndef MODERN_RENDERER_DOM_ADAPTER_H_
#define MODERN_RENDERER_DOM_ADAPTER_H_

#include <string>
#include <vector>
#include <memory>
#include <map>

namespace netscape {
namespace modern {

/**
 * DOMAdapter: Converts legacy Netscape DOM structures to modern HTML5 DOM
 * 
 * Handles:
 * - HTML4 → HTML5 element mapping
 * - Deprecated attribute handling
 * - Legacy JavaScript API translation
 * - Graceful degradation for unsupported features
 */
class DOMAdapter {
 public:
  struct Element {
    std::string tag_name;
    std::string id;
    std::vector<std::string> classes;
    std::map<std::string, std::string> attributes;
    std::vector<std::shared_ptr<Element>> children;
    std::string text_content;
  };

  DOMAdapter();
  ~DOMAdapter();

  // Parse legacy HTML and convert to modern structure
  std::shared_ptr<Element> ParseHTML(const std::string& html);
  
  // Convert Element tree to modern HTML5
  std::string ToHTML5(const std::shared_ptr<Element>& root);
  
  // Handle deprecated HTML4 tags and attributes
  std::string ModernizeTag(const std::string& legacy_tag);
  std::string ModernizeAttributes(const std::string& tag, const std::map<std::string, std::string>& attrs);

  // Query and manipulate DOM
  std::shared_ptr<Element> QuerySelector(const std::shared_ptr<Element>& root, const std::string& selector);
  std::vector<std::shared_ptr<Element>> QuerySelectorAll(const std::shared_ptr<Element>& root, const std::string& selector);

 private:
  std::string ConvertElement(const std::shared_ptr<Element>& elem, int depth = 0);
};

}  // namespace modern
}  // namespace netscape

#endif  // MODERN_RENDERER_DOM_ADAPTER_H_
