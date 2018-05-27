#pragma once

class SDLTexture;

#include <SDL.h>

#include "core.h"
#include "ASprite.h"

class ENGINE_CLASS SDLSprite : public ASprite
{
public:
    SDLSprite();
    ~SDLSprite() override;

    ATexture* GetTexture() override;
    void SetTexture(ATexture* texture) override;
private:
    SDLTexture* tex;
};