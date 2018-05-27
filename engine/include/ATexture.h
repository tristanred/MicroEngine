#pragma once

class ARenderer;

#include <cstdint>

#include "core.h"
#include "Geometry.h"

class ENGINE_CLASS ATexture
{
public:
    explicit ATexture(ARenderer* renderer);
    virtual ~ATexture();

    virtual FSize GetSize();
    virtual void SetSize(FSize size);

    virtual void SetColor(uint32_t color) = 0;

protected:
    ARenderer* BaseRenderer;

    FSize textureSize;
    bool isDirty;
};

