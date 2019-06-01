#include "AbstractFactory.h"

#ifdef SUPPORT_SDL

#include "SDL/SDLText.h"
#include "SDL/SDLTexture.h"
#include "SDL/SDLRenderer.h"
#include "SDL/SDLPlatform.h"
#include "SDL/SDLKeyboard.h"
#include "SDL/SDLMouse.h"

#endif

#ifdef SUPPORT_DIRECTX
#endif

#ifdef SUPPORT_COCOA

#include "Cocoa/CocoaFont.h"
#include "Cocoa/CocoaKeyboard.h"
#include "Cocoa/CocoaMouse.h"
#include "Cocoa/CocoaPlatform.h"
#include "Cocoa/CocoaRenderer.h"
#include "Cocoa/CocoaText.h"
#include "Cocoa/CocoaTexture.h"

#endif

enum ImplementedRenderers AbstractFactory::ActivatedRenderer = RENDERER_COCOA;

AbstractFactory::AbstractFactory()
{
    //AbstractFactory::ActivatedRenderer = RENDERER_SDL;
    AbstractFactory::ActivatedRenderer = RENDERER_COCOA;
}

AbstractFactory::~AbstractFactory()
{
}

ARenderer *AbstractFactory::CreateRenderer()
{
    switch(ActivatedRenderer)
    {
#ifdef SUPPORT_SDL
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating SDL Renderer");
            return new SDLRenderer();
        }
#endif
#if SUPPORT_COCOA
        case RENDERER_COCOA:
        {
            return new CocoaRenderer();
        }
#endif
        default:
        {
            LogError("Factory unable to create an Renderer instance. Activated renderer is %d", ActivatedRenderer);

            return NULL;
        }
    }

    return nullptr;

}

AText* AbstractFactory::CreateText(ARenderer* renderer)
{
    switch (ActivatedRenderer)
    {
#ifdef SUPPORT_SDL
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating SDL Text.");
            return new SDLText(renderer);
        }
#endif
#if SUPPORT_COCOA
        case RENDERER_COCOA:
        {
            return new CocoaText(renderer);
        }
#endif
        default:
        {
            LogError("Factory unable to create a Text instance. Activated renderer is %d", ActivatedRenderer);

            return NULL;
        }
    }

    return nullptr;
}

AFont* AbstractFactory::CreateTextFont(ARenderer* renderer)
{
    switch (ActivatedRenderer)
    {
#ifdef SUPPORT_SDL
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating SDL Font.");
            return new SDLFont();
        }
#endif
#if SUPPORT_COCOA
        case RENDERER_COCOA:
        {
            return new CocoaFont();
        }
#endif
        default:
        {
            LogError("Factory unable to create a Font instance. Activated renderer is %d", ActivatedRenderer);

            return NULL;
        }
    }

    return nullptr;
}

APlatform* AbstractFactory::CreatePlatformHandler(ARenderer* renderer)
{
    switch (ActivatedRenderer)
    {
#ifdef SUPPORT_SDL
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating texture");
            return new SDLPlatform(renderer);
        }
#endif
#if SUPPORT_COCOA
        case RENDERER_COCOA:
        {
            return new CocoaPlatform(renderer);
        }
#endif
        default:
        {
            LogError("Factory unable to create a Platform Handler instance. Activated renderer is %d", ActivatedRenderer);

            return NULL;
        }
    }

    return nullptr;
}

ATexture *AbstractFactory::CreateTexture(ARenderer* renderer)
{
    switch(ActivatedRenderer)
    {
#ifdef SUPPORT_SDL
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating texture");
            return new SDLTexture(renderer);
        }
#endif
#if SUPPORT_COCOA
        case RENDERER_COCOA:
        {
            return new CocoaTexture(renderer);
        }
#endif
        default:
        {
            LogError("Factory unable to create a Texture instance. Activated renderer is %d", ActivatedRenderer);

            return NULL;
        }
    }

    return nullptr;
}

AMouse* AbstractFactory::CreateMouse()
{
    switch (ActivatedRenderer)
    {
#ifdef SUPPORT_SDL
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating Mouse");
            return new SDLMouse();
        }
#endif
#if SUPPORT_COCOA
        case RENDERER_COCOA:
        {
            return new CocoaMouse();
        }
#endif
        default:
        {
            LogError("Factory unable to create a Mouse instance. Activated renderer is %d", ActivatedRenderer);

            return NULL;
        }
    }

    return nullptr;

}

AKeyboard* AbstractFactory::CreateKeyboard()
{
    switch (ActivatedRenderer)
    {
#ifdef SUPPORT_SDL
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating keyboard");
            return new SDLKeyboard();
        }
#endif
#if SUPPORT_COCOA
        case RENDERER_COCOA:
        {
            return new CocoaKeyboard();
        }
#endif
        default:
        {
            LogError("Factory unable to create a Keyboard instance. Activated renderer is %d", ActivatedRenderer);

            return NULL;
        }
    }

    return nullptr;
}
