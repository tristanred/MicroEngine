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

    void SetSize(FSize size) override;

    void SetSolidColor(FSize size, uint32_t color) override;
    void LoadFromFile(const char* filepath) override;

    void FillColor(uint32_t color) override;

    void StrokeRect(FRectangle rect, uint32_t size, uint32_t color);

    void FillRect(FRectangle rect, uint32_t color);

    void FreeTextureMemory() override;
    void ReloadTexture() override;

    ATexture* GetSubTexture(int x, int y, int width, int height) override;

    void CopyFrom(ATexture* other, FPosition sourcePos, FSize sourceSize, FPosition destPos) override;


    void RefreshSDLTexture();

    ARenderer* Renderer;

    // Surface is just a collection of pixels
    SDL_Surface* surf;

    // Texture is a handle to the GPU texture data
    SDL_Texture* tex;
    SDLRenderer* SdlRenderer;



private:
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    const Uint32 rmask = 0xff000000;
    const Uint32 gmask = 0x00ff0000;
    const Uint32 bmask = 0x0000ff00;
    const Uint32 amask = 0x000000ff;
#else
    const Uint32 rmask = 0x000000ff;
    const Uint32 gmask = 0x0000ff00;
    const Uint32 bmask = 0x00ff0000;
    const Uint32 amask = 0xff000000;
#endif
};
