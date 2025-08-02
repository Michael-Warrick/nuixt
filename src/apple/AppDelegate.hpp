#ifndef NUIXT_APPKIT_APPDELEGATE_HPP
#define NUIXT_APPKIT_APPDELEGATE_HPP

// Forward-declare NSWindow to avoid importing Cocoa in C++
#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#else
typedef void NSWindow;
#endif

namespace nuixt::internal {

/// Initializes the macOS NSApplication and installs the delegate + menu bar
void initializeAppKit();

/// Sets the main window pointer for dock icon reopen behavior
void setMainWindowHandle(NSWindow* window);

} // namespace nuixt::internal

#endif // NUIXT_APPKIT_APPDELEGATE_HPP