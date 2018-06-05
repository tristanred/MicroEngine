#include "SDL/SDLSprite.h"

#include "ATexture.h"
#include "SDL/SDLTexture.h"

SDLSprite::SDLSprite(ARenderer* renderer) : ASprite(renderer)
{
    tex = NULL;
    LogTrace("SDLSprite::SDLSprite");
}

SDLSprite::~SDLSprite()
{
    LogTrace("SDLSprite::~SDLSprite");
}

ATexture* SDLSprite::GetTexture()
{
    return dynamic_cast<ATexture*>(this->tex);
}

void SDLSprite::SetTexture(ATexture *texture)
{
    LogTrace("SDLSprite::SetTexture");

    this->tex = static_cast<SDLTexture*>(texture);
}