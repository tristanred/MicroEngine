#ifdef SUPPORT_COCOA

#import <Cocoa/Cocoa.h>

@interface CocoaAppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>

@property NSWindow* win;

@end

#endif