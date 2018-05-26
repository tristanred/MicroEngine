#pragma once

class ARenderer;
class SDLRenderer;

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>

#include "core.h"
#include "ATexture.h"

class ENGINE_CLASS SDLTexture : public ATexture
{
public:
    explicit SDLTexture(ARenderer* renderer);
    ~SDLTexture() override;

    ARenderer* Renderer;

    // Surface is just a collection of pixels
    SDL_Surface* surf;

    // Texture is a handle to the GPU texture data
    SDL_Texture* tex;
    SDLRenderer* SdlRenderer;
};
