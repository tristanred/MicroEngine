#pragma once

class ARenderer;
class SDLRenderer;

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <cstdint>

#include "core.h"
#include "ATexture.h"

class ENGINE_CLASS SDLTexture : public ATexture
{
public:
    explicit SDLTexture(ARenderer* renderer);
    ~SDLTexture() override;

    void SetSize(FSize size) override;
    void SetColor(uint32_t color) override;

    void RefreshSDLTexture();

    ARenderer* Renderer;

    // Surface is just a collection of pixels
    SDL_Surface* surf;

    // Texture is a handle to the GPU texture data
    SDL_Texture* tex;
    SDLRenderer* SdlRenderer;
};
