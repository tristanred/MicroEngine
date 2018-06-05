#pragma once

#include "core.h"

class ARenderable;
class ARenderer;
class ASprite;
class ATexture;
class TextureRepository;

class AMouse;
class AKeyboard;

enum ImplementedRenderers
{
    RENDERER_SDL,
    RENDERER_DIRECTX,
};

class ENGINE_CLASS AbstractFactory
{
public:
    AbstractFactory();
    ~AbstractFactory();

    static enum ImplementedRenderers ActivatedRenderer;

    static ARenderer* CreateRenderer();
    static ASprite* CreateSprite(ARenderer* renderer);
    static ATexture* CreateTexture(ARenderer* renderer);
    static TextureRepository* CreateTextureRepository(ARenderer* renderer);
    static AMouse* CreateMouse();
    static AKeyboard* CreateKeyboard();

};