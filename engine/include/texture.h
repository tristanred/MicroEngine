#pragma once

#include "core.h"

class ENGINE_CLASS ATexture
{
public:
    ATexture();
    ~ATexture();

};

class ARenderer;
class SDLRenderer;

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>

class ENGINE_CLASS SDLTexture : public ATexture
{
public:
    SDLTexture(ARenderer* renderer);
    ~SDLTexture();

    ARenderer* Renderer;
  
    // Surface is just a collection of pixels
    SDL_Surface* surf;

    // Texture is a handle to the GPU texture data
    SDL_Texture* tex;
    SDLRenderer* SdlRenderer;
};
