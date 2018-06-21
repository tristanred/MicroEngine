#include "Viewport.h"

#include "ASprite.h"

Viewport::Viewport()
{
    this->Mode = VP_MODE_STATIC;
    this->FollowingSprite = NULL;
    this->ViewRange = VIEWPORT_NOT_LIMITED_RECT;
}

Viewport::~Viewport()
{
}

void Viewport::Update()
{
    if (this->Mode == VP_MODE_FOLLOW)
    {
        this->CurrentView.AlignCenterOn(&this->FollowingSprite->GetRectangle());

        if (this->ViewRange != VIEWPORT_NOT_LIMITED_RECT)
        {
            this->CurrentView.PushInside(&this->ViewRange);
        }
    }
}

void Viewport::FollowSprite(ASprite* sprite)
{
    if (sprite == NULL)
    {
        this->Mode = VP_MODE_STATIC;
    }
    else
    {
        this->FollowingSprite = sprite;
        this->Mode = VP_MODE_FOLLOW;
    }
}
