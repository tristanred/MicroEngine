#include "Cocoa/CocoaAppDelegate.h"

@implementation CocoaAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application

    NSRect rect;
    rect.origin.x = 0;
    rect.origin.y = 0;
    rect.size.width = 500;
    rect.size.height = 500;

    unsigned int style = (NSWindowStyleMaskTitled|NSWindowStyleMaskClosable|NSWindowStyleMaskMiniaturizable);

    NSWindow* win = [[NSWindow alloc] initWithContentRect:rect styleMask:style backing:NSBackingStoreBuffered defer:FALSE];

    NSButton* butan = [NSButton buttonWithTitle:@"TITEL" target:nil action:nil];
    butan.frame = NSMakeRect(20, 20, 100, 30);
    butan.title = [NSString stringWithUTF8String:"Things"];
    [win.contentView addSubview:butan];
    [win makeKeyAndOrderFront:nil];

}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

@end
