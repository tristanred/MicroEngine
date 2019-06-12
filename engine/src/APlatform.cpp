#include "APlatform.h"

#include "GameEngine.h"

APlatform::APlatform(GameEngine* engine)
{
    LogTrace("APlatform::APlatform");

    this->Renderer = engine->Renderer;
    this->RequestExit = false;
}

APlatform::~APlatform()
{
    LogTrace("APlatform::~APlatform");

}