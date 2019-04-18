#pragma once

class ARenderer;
class ATexture;

#include "core.h"
#include "libtech/geometry.h"
#include "libtech/arraylist.h"

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

    virtual vec2 GetScale();
    virtual void SetScale(float scale);
    virtual void SetScale(float x, float y);
    virtual void SetScale(vec2 scale);

    virtual FRectangle GetRectangle();

    virtual ATexture* GetTexture();
    virtual void SetTexture(ATexture* texture);

    virtual enum POSITION_SYSTEM GetPositionSystem();
    virtual void SetPositionSystem(enum POSITION_SYSTEM value);

    virtual bool IsVisible();
    
    /**
     * Get the current parent or NULL if no parent.
     */
    virtual ARenderable* GetParent();
    
    /**
     * Set this object's parent. Passing NULL will break the current parent
     * relationship.
     */
    virtual void SetParent(ARenderable* object);
    
    /**
     * Add a child to this renderable object. The child will be drawn after this
     * object and will be positioned relative to this object.
     */
    virtual void AddChild(ARenderable* object);
    
    /**
     * Remove a child from this object's children collection.
     */
    virtual void RemoveChild(ARenderable* object);
    
    /**
     * Get the list of children of this object.
     */
    virtual ArrayList<ARenderable*>* GetChildren();

    /**
     * The PreDraw hook is called before any information is queried from this object.
     */
    virtual void OnPreDraw();

    /**
     * The PostDraw hook is called after the texture was drawn to the context.
     */
    virtual void OnPostDraw();

protected:
    ARenderer* Renderer;
    
    ARenderable* Parent;
    ArrayList<ARenderable*>* Children;

    ATexture* texture;

    enum POSITION_SYSTEM PositionSystem;
    FPosition position;
    FSize size;
    vec2 scale;

    bool isVisible;
};
