#include "AbstractFactory.h"

#if SUPPORT_SDL == 1

#include "SDL/SDLSprite.h"
#include "SDL/SDLTexture.h"
#include "SDL/SDLRenderer.h"

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

ASprite *AbstractFactory::CreateSprite()
{
    switch(ActivatedRenderer)
    {
#if SUPPORT_SDL == 1
        case RENDERER_SDL:
        {
            return new SDLSprite();
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
