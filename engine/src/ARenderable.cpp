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
    isVisible = true;
}

ARenderable::~ARenderable()
{
    LogTrace("ARenderable::~ARenderable");
}

FRectangle ARenderable::GetRectangle()
{
    return FRectangle(this->position, this->size);
}

FPosition ARenderable::GetPosition()
{
    return this->position;
}

void ARenderable::SetPosition(FPosition position)
{
    this->position = position;
}

void ARenderable::SetPosition(float x, float y)
{
    this->position.X = x;
    this->position.Y = y;
}

FSize ARenderable::GetSize()
{
    return this->size;
}

void ARenderable::SetSize(FSize size)
{
    this->size = size;
}

void ARenderable::SetSize(float w, float h)
{
    this->size.Width = w;
    this->size.Height = h;
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

bool ARenderable::IsVisible()
{
    return isVisible;
}
