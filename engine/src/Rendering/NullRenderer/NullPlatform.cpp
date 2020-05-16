#include "Rendering/NullRenderer/NullPlatform.h"

NullPlatform::NullPlatform(GameEngine* engine) : APlatform(engine)
{
    this->RequestExit = false;
}

NullPlatform::~NullPlatform() {}

void NullPlatform::HandleEvents() {}

void NullPlatform::Shutdown() {}
