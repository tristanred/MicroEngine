#include "ARenderable.h"

#include "ATexture.h"

ARenderable::ARenderable(ARenderer* renderer)
{
    LogTrace("ARenderable::ARenderable");

    this->Renderer = renderer;

    this->texture = NULL;

    this->size = FSize(0, 0);
    this->position = FPosition(0, 0);
}

ARenderable::~ARenderable()
{
    LogTrace("ARenderable::~ARenderable");
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
