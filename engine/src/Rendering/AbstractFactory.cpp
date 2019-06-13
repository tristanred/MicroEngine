#include "Rendering/AbstractFactory.h"

#include "GameEngine.h"

#if SUPPORT_SDL == 1

#include "Rendering/SDL/SDLText.h"
#include "Rendering/SDL/SDLTexture.h"
#include "Rendering/SDL/SDLRenderer.h"
#include "Rendering/SDL/SDLPlatform.h"
#include "Rendering/SDL/SDLKeyboard.h"
#include "Rendering/SDL/SDLMouse.h"

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

AText* AbstractFactory::CreateText(GameEngine* engine)
{
    switch (ActivatedRenderer)
    {
#if SUPPORT_SDL == 1
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating SDL Text.");
            return new SDLText(engine);
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

AFont* AbstractFactory::CreateTextFont(GameEngine* engine)
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

APlatform* AbstractFactory::CreatePlatformHandler(GameEngine* engine)
{
    switch (ActivatedRenderer)
    {
#if SUPPORT_SDL == 1
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating texture");
            return new SDLPlatform(engine);
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

ATexture *AbstractFactory::CreateTexture(GameEngine* engine)
{
    switch(ActivatedRenderer)
    {
#if SUPPORT_SDL == 1
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating texture");
            return new SDLTexture(engine->Renderer);
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
