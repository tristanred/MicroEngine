#include "TextureRepository.h"

#include <SDL_rwops.h>
#include <SDL_image.h>

#include "libtech/filecache.h"
#include "ARenderer.h"
#include "SDL/SDLTexture.h"

TextureRepository::TextureRepository(ARenderer *renderer)
{
    LogTrace("TextureRepository::TextureRepository");

    this->Renderer = renderer;

    this->Cache = new FileCache();
}

TextureRepository::~TextureRepository()
{
    delete(this->Cache);
}

ATexture* TextureRepository::LoadFromFile(const char* filepath)
{
    size_t fileLength = 0;
    uint8_t* data = this->Cache->ReadFileContents(filepath, &fileLength);

    SDL_RWops* stream = SDL_RWFromMem(data, (int)fileLength);

    SDL_Surface* surface = IMG_Load_RW(stream, false);

    SDLTexture* newTexture = new SDLTexture(this->Renderer, surface);

    return newTexture;
}

ATexture* TextureRepository::GetBySolidColor(uint32_t color)
{
    return nullptr;
}
