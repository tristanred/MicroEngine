#pragma once

#include "core.h"

class ARenderable;

class ENGINE_CLASS ARenderer
{
public:
    ARenderer();
    virtual ~ARenderer();

    virtual void Initialize();

    virtual void Draw(ARenderable* sprite) = 0;
};
