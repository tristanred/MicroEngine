#include "AbstractFactory.h"

#if SUPPORT_SDL == 1

#include "SDL/SDLText.h"
#include "SDL/SDLTexture.h"
#include "SDL/SDLRenderer.h"
#include "SDL/SDLPlatform.h"
#include "SDL/SDLKeyboard.h"
#include "SDL/SDLMouse.h"

#endif

#if SUPPORT_DIRECTX == 0
#endif

enum ImplementedRenderers AbstractFactory::ActivatedRenderer = RENDERER_SDL;

AbstractFactory::AbstractFactory()
{
    AbstractFactory::ActivatedRenderer = RENDERER_SDL;
}

AbstractFactory::~AbstractFactory()
{
}

ARenderer *AbstractFactory::CreateRenderer()
{
    switch(ActivatedRenderer)
    {
#if SUPPORT_SDL == 1
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating SDL Renderer");
            return new SDLRenderer();
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
#if SUPPORT_SDL == 1
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating SDL Text.");
            return new SDLText(renderer);
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
#if SUPPORT_SDL == 1
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating SDL Font.");
            return new SDLFont();
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
#if SUPPORT_SDL == 1
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating texture");
            return new SDLPlatform(renderer);
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
#if SUPPORT_SDL == 1
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating texture");
            return new SDLTexture(renderer);
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
#if SUPPORT_SDL == 1
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating Mouse");
            return new SDLMouse();
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
#if SUPPORT_SDL == 1
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating keyboard");
            return new SDLKeyboard();
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
