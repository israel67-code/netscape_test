#ifndef MODERN_RENDERER_PAINT_BACKEND_H_
#define MODERN_RENDERER_PAINT_BACKEND_H_

#include <string>
#include <memory>
#include "include/cef_render_handler.h"

namespace netscape {
namespace modern {

/**
 * PaintBackend: Modern rendering using Skia (same as Chromium)
 * 
 * Replaces legacy software rendering with:
 * - GPU acceleration (where available)
 * - Antialiasing and subpixel rendering
 * - Advanced compositing
 * - Hardware-accelerated CSS transforms
 */
class PaintBackend : public CefRenderHandler {
 public:
  PaintBackend();
  ~PaintBackend() override;

  // CefRenderHandler implementation
  void OnPaint(CefRefPtr<CefBrowser> browser,
               ParentWindowHandle parent_window_handle,
               int x, int y, const CefRect& dirtyRect,
               const void* buffer, int width, int height) override;

  // Rendering methods
  bool RenderToPNG(const std::string& filepath, int width, int height);
  bool RenderToJPEG(const std::string& filepath, int width, int height, int quality = 85);
  bool RenderToSVG(const std::string& filepath, int width, int height);

  // Performance features
  void EnableGPUAcceleration(bool enable);
  void SetAntialiasing(bool enable);
  void SetSubpixelRendering(bool enable);

  // Frame callback
  using FrameCallback = std::function<void(const void* buffer, int width, int height)>;
  void SetFrameCallback(FrameCallback callback);

 private:
  bool gpu_acceleration_enabled_;
  bool antialiasing_enabled_;
  bool subpixel_rendering_enabled_;
  FrameCallback frame_callback_;
};

}  // namespace modern
}  // namespace netscape

#endif  // MODERN_RENDERER_PAINT_BACKEND_H_
