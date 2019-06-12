#pragma once

#include "core.h"

class GameModule;
class GameEngine;

class ENGINE_CLASS GameObject
{
public:
    GameObject();
    ~GameObject();

    virtual void Setup(GameModule* currentModule);

    virtual void Update(unsigned int deltaTime);

protected:
    GameModule* Owner;

    GameEngine* GetEngine();

    long DeltaTime();

private:
    // Some debug properties
    unsigned int lastUpdateTime;
};
