#pragma once

#include "core.h"

#include "libtech/geometry.h"
#include "ARenderable.h"
#include <libtech/arraylist.h>

class ARenderable;
class ATexture;
class ConfigFile;
class FileCache;
class Viewport;
class Asset;
class ResourceManager;

struct RendererParameters
{
    char window_title[256];
    int window_width;
    int window_height;

    float renderScaleX;
    float renderScaleY;
};

struct TextureDrawOptions
{
    enum POSITION_SYSTEM PosSystem;
};

class ENGINE_CLASS ARenderer
{
public:
    ARenderer();
    virtual ~ARenderer();

    FileCache* Cache; // Set externally, may be NULL if no cache is enabled
    ResourceManager* Resman;
    Viewport* RenderViewport;

    // Methods to be managed by the concrete class
    virtual bool Initialize() = 0;
    virtual bool Initialize(ConfigFile* config) = 0;
    virtual bool Initialize(RendererParameters* params) = 0;

    virtual void Draw(ARenderable* sprite) = 0;
    virtual void DrawTexture(ATexture*tex, float posX, float posY) = 0;
    virtual void DrawTexture(ATexture*tex, float posX, float posY, struct TextureDrawOptions* opt) = 0;

    virtual ATexture* CreateTexture() = 0;
    virtual ATexture* CreateTexture(const char* filepath);
    virtual ATexture* CreateTexture(Asset* asset);
    virtual ATexture* CreateTexture(void* data, int length) = 0;
    
    virtual void DeleteTexture(ATexture* texture) = 0;

    virtual FSize GetWindowSize() = 0;

    virtual void BeginDraw() = 0;
    virtual void EndDraw() = 0;
    virtual void Shutdown() = 0;

    // Utility methods provided by the base ARenderer class
    
    ArrayList<ATexture*>* CreateTextureList(const char* fileNames[], int length);
    
    ArrayList<ATexture*>* LoadFrames(const char* path);
};
