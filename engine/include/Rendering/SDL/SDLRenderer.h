#pragma once

#ifdef SUPPORT_SDL

#include <SDL.h>

#include "Rendering/ARenderer.h"
#include "Rendering/ASprite.h"
#include "Rendering/ATexture.h"
#include "core.h"

class ENGINE_CLASS SDLRenderer : public ARenderer
{
public:
    SDL_Renderer* gameRenderer;
    SDL_Window* mainWindow;

    SDLRenderer();
    ~SDLRenderer() override;

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

    SDL_Texture* BuildTexture(SDL_Surface* surface);

    FSize GetWindowSize() override;

    bool screenshotRequested;
    void ScreenshotNextFrame() override;
    void SaveToFile(RenderableObject* object, const char* path) override;
    void DrawHierarchy(RenderableObject* object);
};
#endif