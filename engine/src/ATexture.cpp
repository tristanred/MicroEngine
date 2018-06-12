#include "ATexture.h"

#include "ARenderer.h"

ATexture::ATexture(ARenderer* renderer)
{
    LogTrace("ATexture::ATexture");

    this->BaseRenderer = renderer;
    loadedTexturePath = NULL;

    textureSize = FSize(0, 0);
    isDirty = true;
}

ATexture::~ATexture()
{
    LogTrace("ATexture::~ATexture");
}

void ATexture::SetSize(FSize size)
{
    this->textureSize = size;
}

const char* ATexture::GetTexturePath()
{
    if (this->loadedTexturePath == NULL)
    {
        return "";
    }
    else
    {
        return this->loadedTexturePath;
    }
}

FSize ATexture::GetSize()
{
    return this->textureSize;
}
