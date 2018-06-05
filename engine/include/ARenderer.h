#pragma once

#include "core.h"

#include "libtech/Geometry.h"

class ARenderable;
class ATexture;
class ConfigFile;

struct RendererParameters
{
    char *window_title;
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

    virtual void Initialize() = 0;
    virtual void Initialize(ConfigFile* config) = 0;
    virtual void Initialize(RendererParameters* params) = 0;

    virtual void Draw(ARenderable* sprite) = 0;
    virtual ATexture* CreateTexture() = 0;

    virtual FSize GetWindowSize() = 0;

    virtual void BeginDraw();
    virtual void EndDraw();
    virtual void Shutdown() = 0;
};
