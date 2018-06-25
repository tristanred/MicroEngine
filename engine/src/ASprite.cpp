#include "ASprite.h"

#include "libtech/geometry.h"

ASprite::ASprite(ARenderer* renderer) : ARenderable(renderer)
{
    LogTrace("ASprite::ASprite");

    this->position.X = 0;
    this->position.Y = 0;

    this->size.Width = 0;
    this->size.Height = 0;
}

ASprite::~ASprite()
{
    LogTrace("ASprite::~ASprite");
}
