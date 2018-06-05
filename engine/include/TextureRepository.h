#pragma once

class ATexture;
class ARenderer;
class FileCache;

#include <cstdint>
using namespace std;

#include "core.h"
#include "libtech/Geometry.h"

class ENGINE_CLASS TextureRepository
{
public:
    explicit TextureRepository(ARenderer* renderer);
    virtual ~TextureRepository();

    virtual ATexture* LoadFromFile(const char* filepath);
    virtual ATexture* GetSolidColorTexture(FSize textureSize, uint32_t color) = 0;

protected:
    ARenderer* Renderer;
    FileCache* Cache;
};