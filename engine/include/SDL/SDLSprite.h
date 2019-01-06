#pragma once

class SDLTexture;

#include <SDL.h>

#include "core.h"
#include "ASprite.h"

class ENGINE_CLASS SDLSprite : public ASprite
{
public:
    SDLSprite(ARenderer* renderer);
    ~SDLSprite() override;
};