#pragma once

class GameEngine;
class ARenderable;
class ASprite;
class ARenderer;

#include <list>

#include "core.h"

class GameEngine;

class ENGINE_CLASS GameModule
{
public:
    GameModule(GameEngine* engine);
    ~GameModule();

    std::list<ARenderable*>* Objects;

    GameEngine* Engine;

    ASprite* CreateSprite();
    
    virtual void Update();
    virtual void Draw(ARenderer* renderer);
};