#pragma once

#include "core.h"

class ENGINE_CLASS ASprite
{
public:
    ASprite();
    ~ASprite();
    
    virtual void Draw() = 0;
};


#include <SDL2/SDL.h>

class ENGINE_CLASS SDLSprite : public ASprite
{
public:
    SDLSprite();
    ~SDLSprite();
};