#include <SDL_rwops.h>
#include <SDL_surface.h>
#include <SDL/SDLTexture.h>
#include <SDL_image.h>
#include "SDL/SDLTextureRepository.h"

#include "ARenderer.h"
#include "libtech/filecache.h"

SDLTextureRepository::SDLTextureRepository(ARenderer *renderer) : TextureRepository(renderer)
{
    LogTrace("SDLTextureRepository::SDLTextureRepository");
}

SDLTextureRepository::~SDLTextureRepository() = default;

ATexture* SDLTextureRepository::LoadFromFile(const char *filepath)
{
    size_t fileLength = 0;
    uint8_t* data = this->Cache->ReadFileContents(filepath, &fileLength);

    SDL_RWops* stream = SDL_RWFromMem(data, (int)fileLength);

    SDL_Surface* surface = IMG_Load_RW(stream, false);

    SDLTexture* newTexture = new SDLTexture(this->Renderer, surface);

    return newTexture;
}

ATexture* SDLTextureRepository::GetSolidColorTexture(FSize textureSize, uint32_t color)
{
    SDL_Surface* newSurface = SDL_CreateRGBSurface(0, textureSize.Width, textureSize.Height, 32, 0, 0, 0, 0);

    SDL_FillRect(newSurface, NULL, color);

    SDLTexture* newTexture = new SDLTexture(this->Renderer, newSurface);

    return newTexture;
}