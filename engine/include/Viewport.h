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
    
    void Update();
    
    void FollowSprite(ASprite* sprite);

private:
    ASprite* FollowingSprite;
};