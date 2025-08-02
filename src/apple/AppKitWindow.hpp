#ifndef NUIXT_APPKIT_WINDOW_HPP
#define NUIXT_APPKIT_WINDOW_HPP

#include "nuixt/Window.hpp"

#ifdef __OBJC__
@class NSWindow;
#else
typedef void NSWindow;
#endif

namespace nuixt {
class AppKitWindow : public Window {
public:
  explicit AppKitWindow(const Properties &properties);
  ~AppKitWindow() override;

  void show() override;
  void hide() override;
  void setTitle(const std::string &title) override;
  void pollEvents() override;
  bool shouldClose() const override;

  void *nativeHandle() const override;

private:
  NSWindow *m_nsWindow = nullptr;
  bool m_shouldClose = false;
};

} // namespace nuixt

#endif // NUIXT_APPKIT_WINDOW_HPP