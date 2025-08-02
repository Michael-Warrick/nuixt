#include "AppKitWindow.hpp"
#include "AppDelegate.hpp"
#import <Cocoa/Cocoa.h>

namespace nuixt {

AppKitWindow::AppKitWindow(const Properties &properties) {
    nuixt::internal::initializeAppKit();

    NSRect rect = NSMakeRect(0, 0, properties.width, properties.height);
    NSUInteger style = NSWindowStyleMaskTitled |
                       NSWindowStyleMaskClosable |
                       NSWindowStyleMaskResizable |
                       NSWindowStyleMaskMiniaturizable;

    NSWindow *window = [[NSWindow alloc] initWithContentRect:rect
                                                   styleMask:style
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO];

    [window setTitle:[NSString stringWithUTF8String:properties.title.c_str()]];
    [window setReleasedWhenClosed:NO];
    [window center];
    [window makeKeyAndOrderFront:nil];

    [NSApp activateIgnoringOtherApps:YES];

    nuixt::internal::setMainWindowHandle(window);

    m_nsWindow = window;
}

AppKitWindow::~AppKitWindow() {
    if (m_nsWindow) {
        NSWindow *window = (__bridge NSWindow *)m_nsWindow;
        [window orderOut:nil]; // Just hide it — don’t release it
        m_nsWindow = nullptr;
    }
}

void AppKitWindow::show() {
    NSWindow *window = (__bridge NSWindow *)m_nsWindow;
    [window makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
}

void AppKitWindow::hide() {
    NSWindow *window = (__bridge NSWindow *)m_nsWindow;
    [window orderOut:nil];
}

void AppKitWindow::setTitle(const std::string &title) {
    NSWindow *window = (__bridge NSWindow *)m_nsWindow;
    [window setTitle:[NSString stringWithUTF8String:title.c_str()]];
}

void AppKitWindow::pollEvents() {
    @autoreleasepool {
        NSEvent *event;
        while ((event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                           untilDate:[NSDate distantPast]
                                              inMode:NSDefaultRunLoopMode
                                             dequeue:YES])) {
            [NSApp sendEvent:event];
            [NSApp updateWindows];
        }
    }
}

bool AppKitWindow::shouldClose() const {
    return false; // TODO: track close requests if desired
}

void* AppKitWindow::nativeHandle() const {
    return m_nsWindow;
}

} // namespace nuixt