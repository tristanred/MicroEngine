#pragma once

class ARenderer;

#include <cstdint>

#include "core.h"
#include "libtech/geometry.h"
#include <libtech/arraylist.h>

class ENGINE_CLASS ATexture
{
public:
    explicit ATexture(ARenderer* renderer);
    virtual ~ATexture();

    // Texture modification methods, calling any of them will probably reset the texture
    virtual void SetSolidColor(FSize size, uint32_t color) = 0;
    virtual void LoadFromFile(const char* filepath) = 0;

    virtual FSize GetSize();
    virtual void SetSize(FSize size);

    virtual void FillColor(uint32_t color) = 0;

    virtual void FreeTextureMemory() = 0;
    virtual void ReloadTexture() = 0;

    virtual const char* GetTexturePath();

    virtual ATexture* GetSubTexture(int x, int y, int width, int height) = 0;

    virtual ArrayList<ATexture*>* SplitTexture(int splits);
    virtual ArrayList<ATexture*>* SplitTexture(int rows, int columns);
    virtual ArrayList<ATexture*>* SplitTexture(FRectangle pieceSize);

protected:
    ARenderer* BaseRenderer;
    const char* loadedTexturePath;

    FSize textureSize;
    bool isDirty;
};
