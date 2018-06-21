#pragma once

class ARenderer;
class ATexture;

#include "core.h"
#include "libtech/geometry.h"

enum POSITION_SYSTEM
{
    VIEWPORT_STATIC,
    VIEWPORT_RELATIVE
};

class ENGINE_CLASS ARenderable
{
public:
    ARenderable(ARenderer* renderer);
    virtual ~ARenderable();

    virtual FPosition GetPosition();
    virtual void SetPosition(FPosition position);

    virtual FSize GetSize();
    virtual void SetSize(FSize size);

    virtual FRectangle GetRectangle();

    virtual ATexture* GetTexture();
    virtual void SetTexture(ATexture* texture);

    virtual enum POSITION_SYSTEM GetPositionSystem();
    virtual void SetPositionSystem(enum POSITION_SYSTEM value);

protected:
    ARenderer* Renderer;

    ATexture* texture;

    enum POSITION_SYSTEM PositionSystem;
    FPosition position;
    FSize size;
};
