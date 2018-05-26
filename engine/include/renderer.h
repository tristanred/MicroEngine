#pragma once

#include "core.h"

class ENGINE_CLASS ARenderer
{
public:
    ARenderer();
    virtual ~ARenderer();

    virtual void Initialize();
};


#include <SDL2/SDL.h>

class ENGINE_CLASS SDLRenderer : public ARenderer
{
public:
    SDLRenderer();
    ~SDLRenderer() override;

    void Initialize() override;
};