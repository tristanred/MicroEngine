#pragma once

#include "core.h"

class GameModule;
class GameEngine;

class ENGINE_CLASS GameObject
{
public:
    GameObject(GameEngine* engine);
    ~GameObject();

    virtual void Update(unsigned int deltaTime);

protected:
    GameEngine* GetEngine();

    long DeltaTime();

private:
    GameEngine* engine;

    // Some debug properties
    unsigned int lastUpdateTime;
};
