#pragma once

#include "core.h"

class ARenderable;
class ARenderer;
class ASprite;
class AText;
class AFont;
class ATexture;
class APlatform;

class AMouse;
class AKeyboard;

enum ImplementedRenderers
{
    RENDERER_SDL,
    RENDERER_DIRECTX,
};

/**
 * The Abstract factory is used to generate concrete type implementations 
 * depending on the current renderer. This class is at the core of the 
 * Abstract Graphic Layer system. Everytime a class from the outside need to 
 * create a sprite or a texture, it must ask the AbstractFactory for it.
 * 
 * From within a specific library, there is no need to go through this factory.
 * For example, from a SDLSprite we can create a new SDLTexture manually
 * because we know that SDL is the current renderer anyway.
 * 
 * The way to detect which renderer is a mix of #define depending on the 
 * platform and a list of implemented renderers. Since SDL is the only
 * implemented renderer the checking isn't really correct.
 */
class ENGINE_CLASS AbstractFactory
{
public:
    AbstractFactory();
    ~AbstractFactory();

    static enum ImplementedRenderers ActivatedRenderer;

    static ARenderer* CreateRenderer();
    static ASprite* CreateSprite(ARenderer* renderer);
    static AText* CreateText(ARenderer* renderer);
    static ATexture* CreateTexture(ARenderer* renderer);
    static AMouse* CreateMouse();
    static AKeyboard* CreateKeyboard();
    static AFont* CreateTextFont(ARenderer* Renderer);
    static APlatform* CreatePlatformHandler(ARenderer* Renderer);
};