#include "ASprite.h"

#include "libtech/geometry.h"

ASprite::ASprite(ARenderer* renderer) : ARenderable(renderer)
{
    LogTrace("ASprite::ASprite");

    this->position.X = 0;
    this->position.Y = 0;

    this->size.Width = 100;
    this->size.Height = 100;
}

ASprite::~ASprite()
{
    LogTrace("ASprite::~ASprite");
}

FPosition ARenderable::GetPosition()
{
    return this->position;
}

void ARenderable::SetPosition(FPosition position)
{
    this->position = position;
}

FSize ARenderable::GetSize()
{
    return this->size;
}

void ARenderable::SetSize(FSize size)
{
    this->size = size;
}
