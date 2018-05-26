#pragma once

#include "core.h"

#include "geometry.h"

class ENGINE_CLASS ARenderable
{
public:
    ARenderable();
    ~ARenderable();

    virtual FPosition GetPosition();
    virtual void SetPosition(FPosition position);

    virtual FSize GetSize();
    virtual void SetSize(FSize size);

    virtual void* GetTexture() = 0;

protected:
    FPosition position;
    FSize size;

};

class ENGINE_CLASS ASprite : public ARenderable
{
public:
    ASprite();
    ~ASprite();
    
};


#include <SDL2/SDL.h>
class SDLTexture;

class ENGINE_CLASS SDLSprite : public ASprite
{
public:
    SDLSprite();
    ~SDLSprite();

    void* GetTexture() override;
    void SetTexture(SDLTexture* tex);
private:
    SDLTexture* tex;
};