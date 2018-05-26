#include "sprite.h"

ASprite::ASprite()
{
    this->position.X = 0;
    this->position.Y = 0;

    this->size.Width = 100;
    this->size.Height = 100;
}

ASprite::~ASprite()
{
}

SDLSprite::SDLSprite() : ASprite()
{

}

SDLSprite::~SDLSprite()
{

}

void* SDLSprite::GetTexture()
{
    return tex;
}

void SDLSprite::SetTexture(SDLTexture* tex)
{
    this->tex = tex;
}

ARenderable::ARenderable()
{

}

ARenderable::~ARenderable()
{

}

FPosition ARenderable::GetPosition()
{
    return this->position;
}

void ARenderable::SetPosition(FPosition position)
{
    this->position = position;
}

FSize ARenderable::GetSize()
{
    return this->size;
}

void ARenderable::SetSize(FSize size)
{
    this->size = size;
}
