#include "APlatform.h"

#include "ARenderer.h"

APlatform::APlatform(ARenderer* renderer)
{
    LogTrace("APlatform::APlatform");

    this->Renderer = renderer;
    this->RequestExit = false;
}

APlatform::~APlatform()
{
    LogTrace("APlatform::~APlatform");

}