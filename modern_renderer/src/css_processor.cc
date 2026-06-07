#include "include/css_processor.h"
#include <regex>
#include <algorithm>

namespace netscape {
namespace modern {

CSSProcessor::CSSProcessor() {
  // Default responsive breakpoints
  breakpoints_ = {320, 768, 1024, 1440};
}

CSSProcessor::~CSSProcessor() {}

std::vector<CSSProcessor::StyleRule> CSSProcessor::ProcessCSS(const std::string& css) {
  std::vector<StyleRule> rules;
  
  // Simple CSS parser
  std::regex rule_regex("([^{]+)\\{([^}]+)\\}");
  std::smatch match;
  std::string::const_iterator search_start(css.cbegin());
  
  while (std::regex_search(search_start, css.cend(), match, rule_regex)) {
    StyleRule rule;
    rule.selector = match[1].str();
    
    // Parse properties
    std::string properties_str = match[2].str();
    std::regex prop_regex("([^:]+):([^;]+);");
    std::smatch prop_match;
    std::string::const_iterator prop_start(properties_str.cbegin());
    
    while (std::regex_search(prop_start, properties_str.cend(), prop_match, prop_regex)) {
      std::string prop = prop_match[1].str();
      std::string value = prop_match[2].str();
      
      // Trim whitespace
      prop.erase(0, prop.find_first_not_of(" \t"));
      prop.erase(prop.find_last_not_of(" \t") + 1);
      value.erase(0, value.find_first_not_of(" \t"));
      value.erase(value.find_last_not_of(" \t") + 1);
      
      // Modernize the property
      std::string modernized = ModernizeProperty(prop, value);
      rule.properties[prop] = modernized;
      
      prop_start = prop_match.suffix().first;
    }
    
    rules.push_back(rule);
    search_start = match.suffix().first;
  }
  
  return rules;
}

std::string CSSProcessor::ModernizeProperty(const std::string& property, const std::string& value) {
  if (IsDeprecatedProperty(property)) {
    return GetModernReplacement(property);
  }
  
  // Convert old layout properties
  return ConvertLayoutProperty(property, value);
}

std::string CSSProcessor::AddVendorPrefixes(const std::string& property, const std::string& value) {
  // Add vendor prefixes for properties that need them
  if (property == "transform" || property == "transition" || property == "animation") {
    return "-webkit-" + property + ": " + value + "; " +
           "-moz-" + property + ": " + value + "; " +
           property + ": " + value;
  }
  return property + ": " + value;
}

std::string CSSProcessor::ConvertLayoutProperty(const std::string& property, const std::string& value) {
  // Convert table-based layouts to flexbox
  if (property == "float") {
    return "/* replaced with flexbox */ display: flex;";
  }
  
  return value;
}

std::string CSSProcessor::ToCSS3(const std::vector<StyleRule>& rules) {
  std::string css;
  
  for (const auto& rule : rules) {
    css += rule.selector + " {\n";
    
    for (const auto& [prop, val] : rule.properties) {
      css += "  " + prop + ": " + val + ";\n";
    }
    
    css += "}\n\n";
  }
  
  return css;
}

void CSSProcessor::AddResponsiveBreakpoints(const std::vector<int>& breakpoints) {
  breakpoints_ = breakpoints;
  std::sort(breakpoints_.begin(), breakpoints_.end());
}

bool CSSProcessor::IsDeprecatedProperty(const std::string& property) const {
  static const std::vector<std::string> deprecated = {
    "background", "bgcolor", "text", "link", "alink", "vlink"
  };
  
  return std::find(deprecated.begin(), deprecated.end(), property) != deprecated.end();
}

std::string CSSProcessor::GetModernReplacement(const std::string& legacy_property) const {
  static const std::map<std::string, std::string> replacements = {
    {"bgcolor", "background-color"},
    {"background", "background-image"},
  };
  
  auto it = replacements.find(legacy_property);
  if (it != replacements.end()) {
    return it->second;
  }
  
  return legacy_property;
}

}  // namespace modern
}  // namespace netscape
