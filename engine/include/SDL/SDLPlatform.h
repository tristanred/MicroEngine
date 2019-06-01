#pragma once

#ifdef SUPPORT_SDL

class ARenderer;

#include "core.h"
#include "APlatform.h"

class ENGINE_CLASS SDLPlatform : public APlatform
{
public:
    SDLPlatform(ARenderer* renderer);
    ~SDLPlatform();

    void HandleEvents() override;

    void Shutdown() override;
};
#endif