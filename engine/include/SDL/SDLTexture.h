#pragma once

class ARenderer;
class SDLRenderer;

#include <SDL.h>
#include <SDL_surface.h>
#include <cstdint>

#include "core.h"
#include "ATexture.h"
#include "libtech/geometry.h"

class ENGINE_CLASS SDLTexture : public ATexture
{
public:
    explicit SDLTexture(ARenderer* renderer);
    SDLTexture(ARenderer* renderer, SDL_Surface* fromSurface);
    ~SDLTexture() override;

    void SetSolidColor(FSize size, uint32_t color) override;
    void LoadFromFile(const char* filepath) override;

    void FillColor(uint32_t color) override;

    void FreeTextureMemory() override;
    void ReloadTexture() override;

    
    void RefreshSDLTexture();

    ARenderer* Renderer;

    // Surface is just a collection of pixels
    SDL_Surface* surf;

    // Texture is a handle to the GPU texture data
    SDL_Texture* tex;
    SDLRenderer* SdlRenderer;



private:
    FSize TextureSize;
};
