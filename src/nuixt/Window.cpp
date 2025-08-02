#include "nuixt/Window.hpp"

#if defined(_WIN32)
#include "../win32/Win32Window.hpp"
#elif defined(__APPLE__)
#include "../apple/AppKitWindow.hpp"
#elif defined(__linux__)
#include "../gtk/GTKWindow.hpp"
#endif

namespace nuixt {

std::unique_ptr<Window> Window::create(const Properties &properties) {
#if defined(_WIN32)
  return std::make_unique<Win32Window>(properties);
#elif defined(__APPLE__)
  return std::make_unique<AppKitWindow>(properties);
#elif defined(__linux__)
  return std::make_unique<GTKWindow>(properties);
#else
  static_assert(false, "Unsupported platform");
  return nullptr;
#endif
}

} // namespace nuixt