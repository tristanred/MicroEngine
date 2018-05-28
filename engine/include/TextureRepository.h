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
    ~TextureRepository();

    ATexture* LoadFromFile(const char* filepath);
    ATexture* GetBySolidColor(uint32_t color);

private:
    ARenderer* Renderer;
    FileCache* Cache;
};