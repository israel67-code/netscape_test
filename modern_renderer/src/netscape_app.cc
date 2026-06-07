#include "include/netscape_app.h"
#include "include/cef_command_line.h"

namespace netscape::modern {

NetscapeApp::NetscapeApp() {}

void NetscapeApp::OnBeforeChildProcessLaunch(
    CefRefPtr<CefCommandLine> command_line) {
  // Customize command line for child process
}

}  // namespace netscape::modern
