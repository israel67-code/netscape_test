#ifndef MODERN_RENDERER_CEF_CLIENT_H_
#define MODERN_RENDERER_CEF_CLIENT_H_

#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_browser.h"

namespace netscape {
namespace modern {

/**
 * CEF Client: Implements Chromium Embedded Framework client handlers
 * 
 * Handles:
 * - Browser creation and lifecycle
 * - Page load events
 * - Display/rendering callbacks
 * - JavaScript execution
 */
class CEFClient : public CefClient {
 public:
  CEFClient();
  ~CEFClient();

  // Browser event callbacks
  virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override;
  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
  virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override;

  // Get browser instance
  CefRefPtr<CefBrowser> GetBrowser() const { return browser_; }

 private:
  CefRefPtr<CefBrowser> browser_;

  IMPLEMENT_REFCOUNTING(CEFClient);
};

/**
 * CEF App: Implements Chromium Embedded Framework app handler
 */
class CEFApp : public CefApp,
               public CefBrowserProcessHandler {
 public:
  CEFApp();
  ~CEFApp();

  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;

private:
  IMPLEMENT_REFCOUNTING(CEFApp);
};

}  // namespace modern
}  // namespace netscape

#endif  // MODERN_RENDERER_CEF_CLIENT_H_
