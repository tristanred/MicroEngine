#include <SDL_rwops.h>
#include <SDL_surface.h>
#include <SDL/SDLTexture.h>
#include <SDL_image.h>
#include "SDL/SDLTextureRepository.h"

#include "ARenderer.h"
#include "libtech/filecache.h"

SDLTextureRepository::SDLTextureRepository(ARenderer *renderer) : TextureRepository(renderer)
{
}

SDLTextureRepository::~SDLTextureRepository() = default;

ATexture *SDLTextureRepository::LoadFromFile(const char *filepath)
{
    size_t fileLength = 0;
    uint8_t* data = this->Cache->ReadFileContents(filepath, &fileLength);

    SDL_RWops* stream = SDL_RWFromMem(data, (int)fileLength);

    SDL_Surface* surface = IMG_Load_RW(stream, false);

    SDLTexture* newTexture = new SDLTexture(this->Renderer, surface);

    return newTexture;
}

ATexture *SDLTextureRepository::GetBySolidColor(uint32_t color)
{
    return TextureRepository::GetBySolidColor(color);
}

