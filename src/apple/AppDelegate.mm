#import "AppDelegate.hpp"
#import <Cocoa/Cocoa.h>

__strong static NSWindow *gMainWindow = nil;

@interface AppDelegate : NSObject <NSApplicationDelegate>
@end

@implementation AppDelegate

- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag {
    if (!gMainWindow.isVisible) {
        [gMainWindow makeKeyAndOrderFront:nil];
        [NSApp activateIgnoringOtherApps:YES];
    }

    return YES;
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return NO; // Keep app alive when window is closed
}

@end

namespace nuixt::internal {

void initializeAppKit() {
    static bool initialized = false;
    if (initialized) return;

    [NSApplication sharedApplication];

    if (![NSApp mainMenu]) {
        NSMenu *menubar = [[NSMenu alloc] init];
        NSMenuItem *appMenuItem = [[NSMenuItem alloc] init];
        [menubar addItem:appMenuItem];
        [NSApp setMainMenu:menubar];

        NSMenu *appMenu = [[NSMenu alloc] init];
        NSString *appName = [[NSProcessInfo processInfo] processName];
        NSString *quitTitle = [NSString stringWithFormat:@"Quit %@", appName];
        NSMenuItem *quitItem = [[NSMenuItem alloc] initWithTitle:quitTitle
                                                          action:@selector(terminate:)
                                                   keyEquivalent:@"q"];
        [appMenu addItem:quitItem];
        [appMenuItem setSubmenu:appMenu];
    }

    AppDelegate* delegate = [[AppDelegate alloc] init];
    [NSApp setDelegate:delegate];

    [NSApp activateIgnoringOtherApps:YES];
    [NSApp finishLaunching];

    initialized = true;
}

void setMainWindowHandle(NSWindow* window) {
    gMainWindow = window;
}

} // namespace nuixt::internal