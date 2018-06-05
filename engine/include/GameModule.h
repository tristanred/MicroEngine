#pragma once

class GameEngine;
class ARenderable;
class ASprite;
class AText;
class AFont;
class ATexture;
class ARenderer;

#include <list>

#include "core.h"


class ENGINE_CLASS GameModule
{
public:
    explicit GameModule(GameEngine* engine);
    virtual ~GameModule();

    std::list<ARenderable*>* Objects;

    // Get game services
    ARenderer* GetRenderer();
    GameEngine* GetEngine();

    // Create renderer-specific objects.
    ASprite* CreateSprite();
    AText* CreateText();
    AFont* CreateFont();

    virtual void AttachRenderable(ARenderable* object);
    
    virtual void Update();
    virtual void Draw(ARenderer* renderer);

private:
    GameEngine* Engine;

};