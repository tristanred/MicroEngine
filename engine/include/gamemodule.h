#pragma once

class GameEngine;
class ARenderable;
class ASprite;

#include <list>

#include "core.h"

class ENGINE_CLASS GameModule
{
public:
    GameModule();
    ~GameModule();

    std::list<ARenderable*>* Objects;

    ASprite* CreateSprite();
    
    virtual void Update();
    virtual void Draw();
};