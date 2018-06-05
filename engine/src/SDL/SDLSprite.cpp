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