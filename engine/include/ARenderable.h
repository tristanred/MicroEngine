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

/*
 * The ARenderable class is the root type for any object that needs to be drawn
 * on the screen. A renderable has a position on screen and a size. It can
 * return a texture and that texture will be drawn.
 *
 * The are multiple position systems that can be used. A VIEWPORT_STATIC system
 * will use the position directly on the Window. VIEWPORT_RELATIVE is used to
 * position the object relative to the currently selected viewport.
 */
class ENGINE_CLASS ARenderable
{
public:
    ARenderable(ARenderer* renderer);
    virtual ~ARenderable();

    virtual FPosition GetPosition();
    virtual void SetPosition(FPosition position);
    virtual void SetPosition(float x, float y);

    virtual FSize GetSize();
    virtual void SetSize(FSize size);
    virtual void SetSize(float w, float h);

    virtual FRectangle GetRectangle();

    virtual ATexture* GetTexture();
    virtual void SetTexture(ATexture* texture);

    virtual enum POSITION_SYSTEM GetPositionSystem();
    virtual void SetPositionSystem(enum POSITION_SYSTEM value);

    virtual bool IsVisible();

protected:
    ARenderer* Renderer;

    ATexture* texture;

    enum POSITION_SYSTEM PositionSystem;
    FPosition position;
    FSize size;

    bool isVisible;
};
