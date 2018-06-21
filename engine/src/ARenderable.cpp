#include "ARenderable.h"

#include "ATexture.h"

ARenderable::ARenderable(ARenderer* renderer)
{
    LogTrace("ARenderable::ARenderable");

    this->Renderer = renderer;

    this->texture = NULL;

    this->size = FSize(0, 0);
    this->position = FPosition(0, 0);
    this->PositionSystem = VIEWPORT_RELATIVE;
}

ARenderable::~ARenderable()
{
    LogTrace("ARenderable::~ARenderable");
}

FRectangle ARenderable::GetRectangle()
{
    return FRectangle(this->position, this->size);
}

ATexture* ARenderable::GetTexture()
{
    return this->texture;
}

void ARenderable::SetTexture(ATexture* newTexture)
{
    if (this->texture != NULL)
        delete(this->texture);

    this->texture = newTexture;
}

enum POSITION_SYSTEM ARenderable::GetPositionSystem()
{
    return this->PositionSystem;
}

void ARenderable::SetPositionSystem(enum POSITION_SYSTEM value)
{
    this->PositionSystem = value;
}
