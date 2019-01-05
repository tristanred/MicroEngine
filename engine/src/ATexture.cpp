#include "ATexture.h"

#include "ARenderer.h"

ATexture::ATexture(ARenderer* renderer)
{
    this->BaseRenderer = renderer;
    loadedTexturePath = NULL;

    textureSize = FSize(0, 0);
    isDirty = true;
}

ATexture::~ATexture()
{
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

ArrayList<ATexture*>* ATexture::SplitTexture(int splits)
{
    ArrayList<ATexture*>* result = new ArrayList<ATexture*>(splits);

    int splitWidth = this->textureSize.Width / splits;

    int splitStartX = 0;
    int splitStartY = 0;
    for(int i = 0; i < splits; i++)
    {
        ATexture* split = this->GetSubTexture(splitStartX, splitStartY, splitWidth, this->textureSize.Height);

        splitStartX += splitWidth;

        result->Add(split);
    }

    return result;
}

ArrayList<ATexture*>* ATexture::SplitTexture(int rows, int columns)
{
    return NULL;
}

ArrayList<ATexture*>* ATexture::SplitTexture(FRectangle pieceSize)
{
    return NULL;
}