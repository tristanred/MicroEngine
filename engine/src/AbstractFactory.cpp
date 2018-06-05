#include "AbstractFactory.h"

#if SUPPORT_SDL == 1

#include "SDL/SDLSprite.h"
#include "SDL/SDLTexture.h"
#include "SDL/SDLRenderer.h"
#include "SDL/SDLTextureRepository.h"
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
#if SUPPORT_DIRECTX
        case RENDERER_DIRECTX:
        {
            return new DXRenderer();
        }
#endif
        default:
        {
            return NULL;
        }
    }

    return nullptr;

}

ASprite *AbstractFactory::CreateSprite(ARenderer* renderer)
{
    switch(ActivatedRenderer)
    {
#if SUPPORT_SDL == 1
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating SDL Sprite.");
            return new SDLSprite(renderer);
        }
#endif
#if SUPPORT_DIRECTX
        case RENDERER_DIRECTX:
        {
            return new DXSprite();
        }
#endif
        default:
        {
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
#if SUPPORT_DIRECTX
        case RENDERER_DIRECTX:
        {
            return new DXTexture(renderer);
        }
#endif
        default:
        {
            return NULL;
        }
    }

    return nullptr;
}

TextureRepository *AbstractFactory::CreateTextureRepository(ARenderer *renderer)
{
    switch(ActivatedRenderer)
    {
#if SUPPORT_SDL == 1
        case RENDERER_SDL:
        {
            LogTrace("AbstractFactory creating texture repository");

            return new SDLTextureRepository(renderer);
        }
#endif
#if SUPPORT_DIRECTX
        case RENDERER_DIRECTX:
        {
            return new DXTexture(renderer);
        }
#endif
        default:
        {
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
#if SUPPORT_DIRECTX
    case RENDERER_DIRECTX:
    {
        return new DXMouse();
    }
#endif
    default:
    {
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
#if SUPPORT_DIRECTX
    case RENDERER_DIRECTX:
    {
        return new DXKeyboard(renderer);
    }
#endif
    default:
    {
        return NULL;
    }
    }

    return nullptr;
}
