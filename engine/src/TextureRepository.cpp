#include "TextureRepository.h"

#include "libtech/filecache.h"
#include "ARenderer.h"

TextureRepository::TextureRepository(ARenderer *renderer)
{
    LogTrace("TextureRepository::TextureRepository");

    this->Renderer = renderer;

    this->Cache = new FileCache();
}

TextureRepository::~TextureRepository()
{
    LogTrace("TextureRepository::~TextureRepository");

    delete(this->Cache);
}

ATexture* TextureRepository::LoadFromFile(const char* filepath)
{
    return NULL;
}