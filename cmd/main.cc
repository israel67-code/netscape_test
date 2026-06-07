#include <iostream>
#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/wrapper/cef_helpers.h"
#include "../modern_renderer/include/netscape_app.h"
#include "../modern_renderer/include/simple_client.h"
#include "../modern_renderer/include/renderer_bridge.h"

using namespace netscape::modern;

// Platform-specific implementation
#if defined(OS_WIN)
#include <windows.h>

int APIENTRY wWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPTSTR lpCmdLine,
                      int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
#else
int main(int argc, char* argv[]) {
#endif

  std::cout << "=================================" << std::endl;
  std::cout << "Netscape 5.0 Browser" << std::endl;
  std::cout << "Powered by CEF (Chromium Embedded Framework)" << std::endl;
  std::cout << "=================================" << std::endl;
  std::cout << std::endl;

#if defined(OS_WIN)
  CefMainArgs main_args(hInstance);
#else
  CefMainArgs main_args(argc, argv);
#endif

  CefRefPtr<CefApp> app(new NetscapeApp());

  // Execute the secondary process, if any.
  int exit_code = CefExecuteProcess(main_args, app, nullptr);
  if (exit_code >= 0)
    return exit_code;

  // Populate the settings based on command-line arguments.
  CefSettings settings;
  settings.no_sandbox = true;
  settings.log_severity = LOGSEVERITY_INFO;

#if !defined(NDEBUG)
  settings.log_severity = LOGSEVERITY_VERBOSE;
#endif

  // Initialize CEF.
  CefInitialize(main_args, settings, app, nullptr);

  std::cout << "CEF initialized successfully" << std::endl;
  std::cout << std::endl;

  // Create the browser window.
  CefWindowInfo window_info;

#if defined(OS_WIN)
  window_info.SetAsPopup(nullptr, "Netscape 5.0");
#endif

  CefBrowserSettings browser_settings;

  // Create the client instance.
  CefRefPtr<SimpleClient> client(new SimpleClient());

  // Create the browser.
  CefBrowserHost::CreateBrowser(window_info, client, "https://www.example.com",
                                 browser_settings, nullptr, nullptr);

  std::cout << "Browser created, entering message loop..." << std::endl;
  std::cout << std::endl;

  // Enter the message loop.
  CefRunMessageLoop();

  std::cout << "Message loop ended, shutting down..." << std::endl;

  // Shut down CEF.
  CefShutdown();

  std::cout << "Netscape Browser terminated." << std::endl;

  return 0;
}
