#include "include/dom_adapter.h"
#include <regex>
#include <sstream>

namespace netscape {
namespace modern {

DOMAdapter::DOMAdapter() {}

DOMAdapter::~DOMAdapter() {}

std::shared_ptr<DOMAdapter::Element> DOMAdapter::ParseHTML(const std::string& html) {
  // Simple HTML parser - convert legacy HTML to modern structure
  auto root = std::make_shared<Element>();
  root->tag_name = "html";
  
  // Basic parsing logic (simplified)
  std::regex tag_regex("<(/?[^>]+)>");
  std::smatch match;
  std::string::const_iterator search_start(html.cbegin());
  
  while (std::regex_search(search_start, html.cend(), match, tag_regex)) {
    std::string tag = match[1].str();
    
    // Process tag
    auto elem = std::make_shared<Element>();
    elem->tag_name = ModernizeTag(tag);
    
    search_start = match.suffix().first;
  }
  
  return root;
}

std::string DOMAdapter::ToHTML5(const std::shared_ptr<Element>& root) {
  return ConvertElement(root);
}

std::string DOMAdapter::ModernizeTag(const std::string& legacy_tag) {
  // Map HTML4 tags to HTML5 equivalents
  static const std::map<std::string, std::string> tag_map = {
    {"center", "div"},
    {"font", "span"},
    {"marquee", "div"},
    {"bgsound", "audio"},
    {"applet", "object"},
    {"layer", "div"},
    {"ilayer", "span"},
  };
  
  auto it = tag_map.find(legacy_tag);
  if (it != tag_map.end()) {
    return it->second;
  }
  return legacy_tag;
}

std::string DOMAdapter::ModernizeAttributes(const std::string& tag, const std::map<std::string, std::string>& attrs) {
  std::stringstream ss;
  
  for (const auto& [key, value] : attrs) {
    // Skip deprecated attributes
    if (key == "bgcolor" || key == "text" || key == "link" || key == "vlink") {
      continue;  // These should be in CSS
    }
    ss << " " << key << "=\"" << value << "\"";
  }
  
  return ss.str();
}

std::shared_ptr<DOMAdapter::Element> DOMAdapter::QuerySelector(const std::shared_ptr<Element>& root, const std::string& selector) {
  // Simple CSS selector matching
  if (!root) return nullptr;
  
  if (root->tag_name == selector || root->id == selector) {
    return root;
  }
  
  for (const auto& child : root->children) {
    auto result = QuerySelector(child, selector);
    if (result) return result;
  }
  
  return nullptr;
}

std::vector<std::shared_ptr<DOMAdapter::Element>> DOMAdapter::QuerySelectorAll(const std::shared_ptr<Element>& root, const std::string& selector) {
  std::vector<std::shared_ptr<Element>> results;
  
  if (!root) return results;
  
  if (root->tag_name == selector) {
    results.push_back(root);
  }
  
  for (const auto& child : root->children) {
    auto child_results = QuerySelectorAll(child, selector);
    results.insert(results.end(), child_results.begin(), child_results.end());
  }
  
  return results;
}

std::string DOMAdapter::ConvertElement(const std::shared_ptr<Element>& elem, int depth) {
  std::stringstream ss;
  std::string indent(depth * 2, ' ');
  
  ss << indent << "<" << elem->tag_name;
  
  if (!elem->id.empty()) {
    ss << " id=\"" << elem->id << "\"";
  }
  
  if (!elem->classes.empty()) {
    ss << " class=\"";
    for (size_t i = 0; i < elem->classes.size(); ++i) {
      if (i > 0) ss << " ";
      ss << elem->classes[i];
    }
    ss << "\"";
  }
  
  for (const auto& [key, value] : elem->attributes) {
    ss << " " << key << "=\"" << value << "\"";
  }
  
  ss << ">";
  
  if (!elem->text_content.empty()) {
    ss << elem->text_content;
  }
  
  for (const auto& child : elem->children) {
    ss << "\n" << ConvertElement(child, depth + 1);
  }
  
  if (!elem->children.empty()) {
    ss << "\n" << indent;
  }
  
  ss << "</" << elem->tag_name << ">";
  
  return ss.str();
}

}  // namespace modern
}  // namespace netscape
