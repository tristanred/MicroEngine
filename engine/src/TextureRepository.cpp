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
    delete(this->Cache);
}

ATexture* TextureRepository::LoadFromFile(const char* filepath)
{
    return NULL;
}

ATexture* TextureRepository::GetBySolidColor(uint32_t color)
{
    return NULL;
}
