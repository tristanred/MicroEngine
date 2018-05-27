#pragma once

#include "core.h"

class ARenderable;
class ATexture;

class ENGINE_CLASS ARenderer
{
public:
    ARenderer();
    virtual ~ARenderer();

    virtual void Initialize();

    virtual void Draw(ARenderable* sprite) = 0;
    virtual ATexture* CreateTexture() = 0;

    virtual void BeginDraw();
    virtual void EndDraw();
};
