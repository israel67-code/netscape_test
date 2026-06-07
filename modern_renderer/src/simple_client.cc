#include "include/simple_client.h"
#include "include/cef_app.h"
#include <iostream>

namespace netscape::modern {

SimpleClient::SimpleClient() : is_closing_(false) {}

void SimpleClient::OnTitleChange(CefRefPtr<CefBrowser> browser,
                                  const CefString& title) {
  std::cout << "Page title: " << std::string(title) << std::endl;
}

void SimpleClient::CloseAllBrowsers(bool force_close) {
  if (!CefCurrentlyOn(TID_UI)) {
    // Execute on the UI thread.
    CefPostTask(TID_UI,
                base::Bind(&SimpleClient::CloseAllBrowsers, this, force_close));
    return;
  }

  if (browser_) {
    browser_->GetHost()->CloseBrowser(force_close);
  }
}

}  // namespace netscape::modern
