#if SUPPORT_COCOA == 1

#import <Cocoa/Cocoa.h>

@interface CocoaAppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>

@property NSWindow* win;

@end

#endif