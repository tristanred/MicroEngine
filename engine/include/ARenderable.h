#pragma once

class ARenderer;
class ATexture;

#include "core.h"
#include "libtech/Geometry.h"

class ENGINE_CLASS ARenderable
{
public:
    ARenderable(ARenderer* renderer);
    virtual ~ARenderable();

    virtual FPosition GetPosition();
    virtual void SetPosition(FPosition position);

    virtual FSize GetSize();
    virtual void SetSize(FSize size);

    virtual ATexture* GetTexture() = 0;
    virtual void SetTexture(ATexture* texture) = 0;

protected:
    ARenderer* Renderer;

    FPosition position;
    FSize size;

};
