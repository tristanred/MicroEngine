#pragma once

class ARenderer;
class ATexture;

#include "core.h"
#include "libtech/geometry.h"

class ENGINE_CLASS ARenderable
{
public:
    ARenderable(ARenderer* renderer);
    virtual ~ARenderable();

    virtual FPosition GetPosition();
    virtual void SetPosition(FPosition position);

    virtual FSize GetSize();
    virtual void SetSize(FSize size);

    virtual ATexture* GetTexture();
    virtual void SetTexture(ATexture* texture);

protected:
    ARenderer* Renderer;

    ATexture* texture;

    FPosition position;
    FSize size;
};
