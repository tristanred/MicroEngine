#pragma once

#include "core.h"

class ENGINE_CLASS ARenderer
{
public:
    ARenderer();
    ~ARenderer();

    virtual void Initialize();
};


#include <SDL.h>

class ENGINE_CLASS SDLRenderer : public ARenderer
{
public:
    SDLRenderer();
    ~SDLRenderer();

    void Initialize() override;
};