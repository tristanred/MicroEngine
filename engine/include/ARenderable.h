#pragma once

class ATexture;

#include "core.h"
#include "Geometry.h"

class ENGINE_CLASS ARenderable
{
public:
    ARenderable();
    virtual ~ARenderable();

    virtual FPosition GetPosition();
    virtual void SetPosition(FPosition position);

    virtual FSize GetSize();
    virtual void SetSize(FSize size);

    virtual ATexture* GetTexture() = 0;
    virtual void SetTexture(ATexture* texture) = 0;

protected:
    FPosition position;
    FSize size;

};
