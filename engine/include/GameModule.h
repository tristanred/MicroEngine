#pragma once

class GameEngine;
class ARenderable;
class ASprite;
class ARenderer;

#include <list>

#include "core.h"


class ENGINE_CLASS GameModule
{
public:
    explicit GameModule(GameEngine* engine);
    virtual ~GameModule();

    std::list<ARenderable*>* Objects;

    GameEngine* Engine;

    ASprite* CreateSprite();
    
    virtual void Update();
    virtual void Draw(ARenderer* renderer);
};