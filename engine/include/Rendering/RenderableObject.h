#pragma once

class ARenderer;
class ATexture;
class GameEngine;

#include "Game/GameObject.h"
#include "core.h"
#include "libtech/arraylist.h"
#include "libtech/geometry.h"

/**
 * \brief Values indicating the relative position of an object.
 *
 * Current values are VIEWPORT_STATIC to have objects be positioned without
 * regard to the viewport's current position. These items will always be in
 * an absolute position regarding to their parent. VIEWPORT_RELATIVE will
 * be offset by the current viewport position.
 *
 * /remark Actually, I have no idea how well this plays with the container
 * system positioning.
 */
enum POSITION_SYSTEM
{
    VIEWPORT_STATIC,
    VIEWPORT_RELATIVE
};

/**
 * \brief Abstract base class of any renderable object.
 *
 * The RenderableObject class is the root type for any object that needs to be
 * drawn on the screen. A renderable has a position on screen and a size. It can
 * return a texture and that texture will be drawn.
 *
 * All functions of an RenderableObject are virtual but they have
 * implementations that will work without subtyping this class.
 *
 * \remark A note on RenderableObject subtyping : Usually, all instances of
 * RenderableObject and its subtypes will come from the GameEngine through the
 * AbstractFactory. Usually this means those objects are completely managed
 * by the GameEngine classes and not directly implemented by the programmer. In
 * contrast to other types such as ASprite and AText, RenderableObject is not
 * needed to be created by the GameEngine with a platform specific instance and
 * so we can create our own drawable objects by inheriting from
 * RenderableObject.
 */
class ENGINE_CLASS RenderableObject : public GameObject
{
public:
    RenderableObject(GameEngine* engine);
    virtual ~RenderableObject();

    virtual void Show(bool value);

    /**
     * \brief Get the position of this object.
     *
     * If this object has a parent, it will return his position offset by his
     * parent's position (recursively).
     *
     * \return FPosition
     */
    virtual FPosition GetPosition();

    /**
     * \brief Set the position of this object.
     *
     * \param position - Target position
     */
    virtual void SetPosition(FPosition position);

    /**
     * \brief Set the position of this object.
     *
     * \param x - X position
     * \param y - Y position
     */
    virtual void SetPosition(float x, float y);

    virtual void SetPositionAnchored(FPosition position, vec2 anchor);

    /**
     * \brief Get the size of this object.
     *
     * If this object has children, it will return a size that encompasses all
     * of its children.
     *
     * \remark Currently, getting the total size of children is not implemented.
     *
     * \return FSize
     */
    virtual FSize GetSize();

    /**
     * \brief Set the size of this object.
     *
     * \remark This should probably have an effect on the size of the children
     * but nothing like that is implemented yet.
     *
     * \param size - Target size.
     */
    virtual void SetSize(FSize size);

    /**
     * \brief Set the size of this object.
     *
     * \remark This should probably have an effect on the size of the children
     * but nothing like that is implemented yet.
     *
     * \param w - Width
     * \param h - Height
     */
    virtual void SetSize(float w, float h);

    virtual FPolygon GetPolygon();

    /**
     * \brief Get the scale of this object.
     *
     * \return vec2
     */
    virtual vec2 GetScale();

    /**
     * \brief Set the X and Y scale of this object.
     *
     * \param scale - Scale applied to both dimension.
     */
    virtual void SetScale(float scale);

    /**
     * \brief Set scale of this object
     *
     * \param x - X Scale
     * \param y - Y Scale
     */
    virtual void SetScale(float x, float y);

    /**
     * \brief Set the scale of this object.
     *
     * \param scale - Scale applied to each dimension.
     */
    virtual void SetScale(vec2 scale);

    virtual float GetRotation();
    virtual void SetRotation(float angle);

    /**
     * \brief Get the bounds of this object.
     *
     * \return FRectangle
     */
    virtual FRectangle GetRectangle();

    /**
     * \brief Get the texture currently applied.
     *
     * \return ATexture
     */
    virtual ATexture* GetTexture();

    /**
     * \brief Setup from a file, automatically creates a texture and
     * applies it to itself.
     *
     * This sets the sprite to a single texture.
     *
     * \param filepath - Path to load as a texture.
     */
    virtual void SetTexture(const char* filepath);

    /**
     * \brief Set the texture of the object.
     *
     * \param texture - New texture to set.
     */
    virtual void SetTexture(ATexture* texture);

    /**
     * \brief Get the position system currently applied.
     *
     * \return POSITION_SYSTEM
     */
    virtual enum POSITION_SYSTEM GetPositionSystem();

    /**
     * \brief Set the position system of this object.
     *
     * \param value - New position system to use
     */
    virtual void SetPositionSystem(enum POSITION_SYSTEM value);

    /**
     * \brief Checks if this object is visible.
     *
     * If this object has a parent, it will go up the chain to see if any parent
     * is not visible. If a parent is not visible, this object will return false
     * because it would not be shown.
     *
     * \return bool
     */
    virtual bool IsVisible();

    /**
     * \brief Get the current parent or NULL if no parent.
     *
     * \return RenderableObject
     */
    virtual RenderableObject* GetParent();

    /**
     * Set this object's parent. Passing NULL will break the current parent
     * relationship.
     *
     * \param object - New parent object
     */
    virtual void SetParent(RenderableObject* object);

    /**
     * \brief Add a child to this renderable object.
     *
     * The child will be drawn after this object and will be positioned relative
     * to this object.
     *
     * \param object - New child.
     */
    virtual void AddChild(RenderableObject* object);

    /**
     * \brief Remove a child from this renderable object.
     *
     * \param object - Child to remove.
     */
    virtual void RemoveChild(RenderableObject* object);

    /**
     * \brief Get the list of children of this object.
     */
    virtual ArrayList<RenderableObject*>* GetChildren();

    /**
     * \brief Hook method called before this object is drawn.
     *
     * The PreDraw hook is called before any information is queried from this
     * object.
     */
    virtual void OnPreDraw();

    /**
     * \brief Hook method called after this object is drawn.
     *
     * The PostDraw hook is called after the texture was drawn to the context.
     */
    virtual void OnPostDraw();

protected:
    ARenderer* Renderer;

    RenderableObject* Parent;
    ArrayList<RenderableObject*>* Children;

    ATexture* texture;

    enum POSITION_SYSTEM PositionSystem;
    FPosition position;
    FSize size;
    vec2 scale;
    float rotation;

    bool isVisible;
};
