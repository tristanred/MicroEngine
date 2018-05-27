#include "ATexture.h"

#include "ARenderer.h"

ATexture::ATexture(ARenderer* renderer)
{
    this->BaseRenderer = renderer;
}

ATexture::~ATexture()
{

}

void ATexture::SetSize(FSize size)
{
    isDirty = true;
    this->textureSize = size;
}

FSize ATexture::GetSize()
{
    return this->textureSize;
}
