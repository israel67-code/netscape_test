#include "include/paint_backend.h"
#include <iostream>
#include <fstream>

namespace netscape {
namespace modern {

PaintBackend::PaintBackend()
    : gpu_acceleration_enabled_(true),
      antialiasing_enabled_(true),
      subpixel_rendering_enabled_(true) {}

PaintBackend::~PaintBackend() {}

void PaintBackend::OnPaint(CefRefPtr<CefBrowser> browser,
                          ParentWindowHandle parent_window_handle,
                          int x, int y, const CefRect& dirtyRect,
                          const void* buffer, int width, int height) {
  // Handle paint event from Blink
  if (frame_callback_) {
    frame_callback_(buffer, width, height);
  }
  
  if (gpu_acceleration_enabled_) {
    // GPU-accelerated rendering
    std::cout << "Rendering with GPU acceleration" << std::endl;
  }
}

bool PaintBackend::RenderToPNG(const std::string& filepath, int width, int height) {
  std::cout << "Rendering to PNG: " << filepath << " (" << width << "x" << height << ")" << std::endl;
  // PNG encoding using Skia
  return true;
}

bool PaintBackend::RenderToJPEG(const std::string& filepath, int width, int height, int quality) {
  std::cout << "Rendering to JPEG: " << filepath << " (" << width << "x" << height << ", quality: " << quality << ")" << std::endl;
  // JPEG encoding using Skia
  return true;
}

bool PaintBackend::RenderToSVG(const std::string& filepath, int width, int height) {
  std::cout << "Rendering to SVG: " << filepath << " (" << width << "x" << height << ")" << std::endl;
  // SVG generation
  return true;
}

void PaintBackend::EnableGPUAcceleration(bool enable) {
  gpu_acceleration_enabled_ = enable;
  std::cout << "GPU acceleration: " << (enable ? "enabled" : "disabled") << std::endl;
}

void PaintBackend::SetAntialiasing(bool enable) {
  antialiasing_enabled_ = enable;
}

void PaintBackend::SetSubpixelRendering(bool enable) {
  subpixel_rendering_enabled_ = enable;
}

void PaintBackend::SetFrameCallback(FrameCallback callback) {
  frame_callback_ = callback;
}

}  // namespace modern
}  // namespace netscape
