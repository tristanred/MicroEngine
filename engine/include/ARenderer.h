#pragma once

#include "core.h"

#include "libtech/geometry.h"

class ARenderable;
class ATexture;
class ConfigFile;
class TextureRepository;
class FileCache;

struct RendererParameters
{
    char window_title[256];
    int window_width;
    int window_height;

    float renderScaleX;
    float renderScaleY;
};

class ENGINE_CLASS ARenderer
{
public:
    ARenderer();
    virtual ~ARenderer();

    FileCache* Cache; // Set externally, may be NULL if no cache is enabled
    TextureRepository* TextureRepo;

    virtual bool Initialize() = 0;
    virtual bool Initialize(ConfigFile* config) = 0;
    virtual bool Initialize(RendererParameters* params) = 0;

    virtual void Draw(ARenderable* sprite) = 0;
    virtual ATexture* CreateTexture() = 0;
    virtual ATexture* CreateTexture(const char* filepath) = 0;

    virtual FSize GetWindowSize() = 0;

    virtual void BeginDraw() = 0;
    virtual void EndDraw() = 0;
    virtual void Shutdown() = 0;
    virtual void DrawTexture(ATexture*tex, float posX, float posY) = 0;
};
