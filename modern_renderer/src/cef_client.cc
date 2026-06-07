#include "include/cef_client.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"
#include <iostream>
#include <sstream>

namespace netscape {
namespace modern {

// Simple CEF client implementation
class SimpleClient : public CefClient,
                     public CefDisplayHandler,
                     public CefLifeSpanHandler,
                     public CefLoadHandler {
 public:
  SimpleClient() {}

  virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override {
    return this;
  }

  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
    return this;
  }

  virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override {
    return this;
  }

  // CefDisplayHandler methods
  virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                             const CefString& title) override {
    std::cout << "Page title: " << title.ToString() << std::endl;
  }

  // CefLifeSpanHandler methods
  virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {
    std::cout << "Browser created successfully" << std::endl;
  }

  // CefLoadHandler methods
  virtual void OnLoadStart(CefRefPtr<CefBrowser> browser,
                          CefRefPtr<CefFrame> frame,
                          TransitionType transition_type) override {
    std::cout << "Loading: " << frame->GetUrl().ToString() << std::endl;
  }

  virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
                        CefRefPtr<CefFrame> frame,
                        int httpStatusCode) override {
    std::cout << "Load complete (HTTP " << httpStatusCode << ")" << std::endl;
  }

  virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                          CefRefPtr<CefFrame> frame,
                          ErrorCode errorCode,
                          const CefString& errorText,
                          const CefString& failedUrl) override {
    std::cerr << "Load error: " << errorText.ToString() << std::endl;
  }

 private:
  IMPLEMENT_REFCOUNTING(SimpleClient);
};

// App handler
class SimpleApp : public CefApp,
                  public CefBrowserProcessHandler {
 public:
  SimpleApp() {}

  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
    return this;
  }

  virtual void OnContextInitialized() override {
    std::cout << "CEF context initialized" << std::endl;
  }

 private:
  IMPLEMENT_REFCOUNTING(SimpleApp);
};

}  // namespace modern
}  // namespace netscape
