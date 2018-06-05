#include "APlatform.h"

#include "ARenderer.h"

APlatform::APlatform(ARenderer* renderer)
{
    this->Renderer = renderer;
    this->RequestExit = false;
}

APlatform::~APlatform()
{

}