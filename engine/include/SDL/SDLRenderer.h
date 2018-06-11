#pragma once

#include <SDL.h>

#include "core.h"
#include "ARenderer.h"
#include "ASprite.h"
#include "ATexture.h"

class ENGINE_CLASS SDLRenderer : public ARenderer
{
public:
    SDL_Renderer* gameRenderer;
    SDL_Window* mainWindow;

    SDLRenderer();
    ~SDLRenderer() override;

    bool Initialize() override;
    bool Initialize(ConfigFile* config) override;
    bool Initialize(RendererParameters* params) override;

    void Shutdown() override;

    void BeginDraw() override;
    void EndDraw() override;

    void Draw(ARenderable* sprite) override;
    void DrawTexture(ATexture* texture, float posX, float posY) override;

    ATexture* CreateTexture() override;

    SDL_Texture* BuildTexture(SDL_Surface* surface);

    FSize GetWindowSize() override;
};