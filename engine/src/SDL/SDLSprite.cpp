#include "SDL/SDLSprite.h"

#include "ATexture.h"
#include "SDL/SDLTexture.h"

SDLSprite::SDLSprite() : ASprite()
{

}

SDLSprite::~SDLSprite()
{

}

ATexture* SDLSprite::GetTexture()
{
    return (ATexture*)tex;
}

void SDLSprite::SetTexture(ATexture *texture)
{
    this->tex = static_cast<SDLTexture*>(texture);
}