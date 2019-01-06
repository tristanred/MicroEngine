#pragma once

#include "core.h"
#include <GameModule.h>

class ENGINE_CLASS GameObject
{
public:
    GameObject();
    ~GameObject();

    virtual void Setup(GameModule* currentModule);

    virtual void Update(unsigned int deltaTime);
    virtual void Draw();

protected:
    GameModule* Owner;

private:
    // Some debug properties
    unsigned int lastUpdateTime;
    unsigned int lastDrawTime;
};