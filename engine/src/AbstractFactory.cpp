#include "AbstractFactory.h"

#if SUPPORT_SDL == 1

#include "SDL/SDLSprite.h"
#include "SDL/SDLText.h"
#include "SDL/SDLTexture.h"
#include "SDL/SDLRenderer.h"
#include "SDL/SDLTextureRepository.h"
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
#if SUPPORT_DIRECTX
        case RENDERER_DIRECTX:
        {
            return new DXRenderer();
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
            LogError("Factory unable to create a Sprite instance. Activated renderer is %d", ActivatedRenderer);

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
#if SUPPORT_DIRECTX
        case RENDERER_DIRECTX:
        {
            return new DXText();
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

AFont* AbstractFactory::CreateFont(ARenderer* renderer)
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
#if SUPPORT_DIRECTX
        case RENDERER_DIRECTX:
        {
            return new DXFont();
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
#if SUPPORT_DIRECTX
        case RENDERER_DIRECTX:
        {
            return new DXTexture(renderer);
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
#if SUPPORT_DIRECTX
        case RENDERER_DIRECTX:
        {
            return new DXTexture(renderer);
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
            LogError("Factory unable to create a Texture Repo instance. Activated renderer is %d", ActivatedRenderer);

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
#if SUPPORT_DIRECTX
        case RENDERER_DIRECTX:
        {
            return new DXKeyboard(renderer);
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
