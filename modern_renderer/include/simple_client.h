#pragma once

#include "include/cef_client.h"
#include "include/cef_browser.h"
#include <memory>

namespace netscape::modern {

// Client implementation for CEF
class SimpleClient : public CefClient, public CefDisplayHandler {
 public:
  SimpleClient();

  // CefClient methods:
  virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE { return this; }

  // CefDisplayHandler methods:
  virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                             const CefString& title) OVERRIDE;

  CefRefPtr<CefBrowser> GetBrowser() const { return browser_; }
  bool IsClosing() const { return is_closing_; }

  void CloseAllBrowsers(bool force_close);

 protected:
  friend class BrowserWindowListener;

  // After the first browser is created.
  CefRefPtr<CefBrowser> browser_;
  bool is_closing_;

PRIVATE:
  IMPLEMENT_REFCOUNTING(SimpleClient);
};

}  // namespace netscape::modern
