#pragma once

class ASprite;

#include "core.h"
#include "libtech/geometry.h"

#define VIEWPORT_NOT_LIMITED_RECT FRectangle(0, 0, -1, -1)

enum Viewport_Mode
{
    VP_MODE_STATIC,
    VP_MODE_FOLLOW
};

/**
 * \brief Viewport class. This is kind of a 2D camera class.
 *
 * The viewport has some fancy functions to follow a Sprite when it moves, it
 * isn't super nice right now and might get chopped later.
 */
class ENGINE_CLASS Viewport
{
public:
    Viewport();
    ~Viewport();

    // ViewRange is the max positions where the viewport can move to (when following a sprite)
    FRectangle ViewRange;

    // This is where the viewport is right now
    FRectangle CurrentView;
    enum Viewport_Mode Mode;

    /**
     * \brief Update the viewport.
     */
    void Update();

    /**
     * \brief Select sprite to follow.
     *
     * The camera will try to move in order to keep the sprite at the center
     * of the screen.
     *
     * \param sprite - Target sprite.
     */
    void FollowSprite(ASprite* sprite);

private:
    ASprite* FollowingSprite;
};