#pragma once

class ARenderer;

#include <cstdint>

#include "core.h"
#include "libtech/geometry.h"

class ENGINE_CLASS ATexture
{
public:
    explicit ATexture(ARenderer* renderer);
    virtual ~ATexture();

    // Texture modification methods, calling any of them will probably reset the texture
    virtual void SetSolidColor(FSize size, uint32_t color) = 0;
    virtual void LoadFromFile(const char* filepath) = 0;

    virtual FSize GetSize();

    // Setting the size will stretch the image or just set the solid color larger.
    virtual void SetSize(FSize size);

    virtual void FillColor(uint32_t color) = 0;

protected:
    ARenderer* BaseRenderer;

    FSize textureSize;
    bool isDirty;
};
