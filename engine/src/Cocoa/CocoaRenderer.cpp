#if SUPPORT_COCOA == 1

#include "Cocoa/CocoaRenderer.h"
#include "Cocoa/CocoaTexture.h"
#include <Foundation/Foundation.h>
#include <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#include "Cocoa/CocoaAppDelegate.h"

CocoaRenderer::CocoaRenderer()
{

}

CocoaRenderer::~CocoaRenderer()
{

}

bool CocoaRenderer::Initialize()
{
    CocoaAppDelegate* appDel = [CocoaAppDelegate alloc];
    [NSApp setDelegate:appDel];

    NSApplication* app = [NSApplication sharedApplication];

    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    [NSApp activateIgnoringOtherApps:YES];

    app.delegate = appDel;

    [app run];

    return true;
}

bool CocoaRenderer::Initialize(ConfigFile* config)
{
    return this->Initialize();
}

bool CocoaRenderer::Initialize(RendererParameters* params)
{
    return this->Initialize();
}

void CocoaRenderer::Shutdown()
{

}

void CocoaRenderer::BeginDraw()
{

}

void CocoaRenderer::EndDraw()
{

}

void CocoaRenderer::Draw(ARenderable* sprite)
{

}

void CocoaRenderer::DrawTexture(ATexture* texture, float posX, float posY)
{

}

void CocoaRenderer::DrawTexture(ATexture* texture, float posX, float posY, struct TextureDrawOptions* opts)
{

}

ATexture* CocoaRenderer::CreateTexture()
{
    return new CocoaTexture(this);
}

ATexture* CocoaRenderer::CreateTexture(void* data, int length)
{
    return new CocoaTexture(this);
}

void CocoaRenderer::DeleteTexture(ATexture* texture)
{

}

FSize CocoaRenderer::GetWindowSize()
{
    return FSize(0, 0);
}

void CocoaRenderer::ScreenshotNextFrame()
{

}

void CocoaRenderer::SaveToFile(ARenderable* object, const char* path)
{

}

void CocoaRenderer::DrawHierarchy(ARenderable* object)
{

}
#endif
