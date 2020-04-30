#pragma once

#include "Rendering/ARenderer.h"
#include "Rendering/ASprite.h"
#include "Rendering/ATexture.h"
#include "core.h"

class ENGINE_CLASS NullRenderer : public ARenderer
{
public:
    NullRenderer();
    ~NullRenderer() override;

    bool Initialize() override;
    bool Initialize(IConfigProvider* config) override;
    bool Initialize(RendererParameters* params) override;

    void Shutdown() override;

    void BeginDraw() override;
    void EndDraw() override;

    void Draw(RenderableObject* sprite) override;
    void DrawTexture(ATexture* texture, float posX, float posY) override;
    void DrawTexture(ATexture* texture,
                     float posX,
                     float posY,
                     struct TextureDrawOptions* opts) override;

    ATexture* CreateTexture() override;
    ATexture* CreateTexture(void* data, int length) override;

    void DeleteTexture(ATexture* texture) override;

    FSize GetWindowSize() override;

    void ScreenshotNextFrame() override;
    void SaveToFile(RenderableObject* object, const char* path) override;
};