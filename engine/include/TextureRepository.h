#pragma once

class ATexture;
class ARenderer;
class FileCache;

#include <cstdint>
using namespace std;

#include "core.h"

class ENGINE_CLASS TextureRepository
{
public:
    explicit TextureRepository(ARenderer* renderer);
    virtual ~TextureRepository();

    virtual ATexture* LoadFromFile(const char* filepath);
    virtual ATexture* GetBySolidColor(uint32_t color);

protected:
    ARenderer* Renderer;
    FileCache* Cache;
};