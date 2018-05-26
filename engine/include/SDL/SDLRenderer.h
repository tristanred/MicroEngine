#pragma once

#include <SDL2/SDL.h>

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

    void Initialize() override;

    void Draw(ARenderable* sprite) override;

    SDL_Texture* BuildTexture(SDL_Surface* surface);
};