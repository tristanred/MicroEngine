#pragma once

class GameEngine;

#include "Rendering/APlatform.h"
#include "core.h"

class ENGINE_CLASS NullPlatform : public APlatform
{
public:
    NullPlatform(GameEngine* engine);
    ~NullPlatform();

    void HandleEvents() override;

    void Shutdown() override;
};