#pragma once

#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_render_process_handler.h"

namespace netscape::modern {

// App implementation for CEF
class NetscapeApp : public CefApp, public CefBrowserProcessHandler {
 public:
  NetscapeApp();

  // CefApp methods:
  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE {
    return this;
  }

  // CefBrowserProcessHandler methods:
  virtual void OnBeforeChildProcessLaunch(
      CefRefPtr<CefCommandLine> command_line) OVERRIDE;

 private:
  IMPLEMENT_REFCOUNTING(NetscapeApp);
};

}  // namespace netscape::modern
