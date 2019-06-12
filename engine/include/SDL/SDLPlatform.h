#pragma once

#ifdef SUPPORT_SDL

class GameEngine;

#include "core.h"
#include "APlatform.h"

class ENGINE_CLASS SDLPlatform : public APlatform
{
public:
    SDLPlatform(GameEngine* engine);
    ~SDLPlatform();

    void HandleEvents() override;

    void Shutdown() override;
};
#endif