#pragma once

#include "core.h"
#include "ARenderer.h"
#include "ASprite.h"
#include "ATexture.h"


class ENGINE_CLASS CocoaRenderer : public ARenderer
{
public:
    //SDL_Renderer* gameRenderer;
    //SDL_Window* mainWindow;

    CocoaRenderer();
    virtual ~CocoaRenderer() override;

    bool Initialize() override;
    bool Initialize(ConfigFile* config) override;
    bool Initialize(RendererParameters* params) override;

    void Shutdown() override;

    void BeginDraw() override;
    void EndDraw() override;

    void Draw(ARenderable* sprite) override;
    void DrawTexture(ATexture* texture, float posX, float posY) override;
    void DrawTexture(ATexture* texture, float posX, float posY, struct TextureDrawOptions* opts) override;

    ATexture* CreateTexture() override;
    ATexture* CreateTexture(void* data, int length) override;

    void DeleteTexture(ATexture* texture) override;

    //SDL_Texture* BuildTexture(SDL_Surface* surface);

    FSize GetWindowSize() override;

    bool screenshotRequested;
    void ScreenshotNextFrame() override;
    void SaveToFile(ARenderable* object, const char* path) override;
    void DrawHierarchy(ARenderable* object);
};
