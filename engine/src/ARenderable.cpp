#include "ARenderable.h"

ARenderable::ARenderable(ARenderer* renderer)
{
    LogTrace("ARenderable::ARenderable");

    this->Renderer = renderer;

    this->size = FSize(0, 0);
    this->position = FPosition(0, 0);
}

ARenderable::~ARenderable()
{
    LogTrace("ARenderable::~ARenderable");
}
