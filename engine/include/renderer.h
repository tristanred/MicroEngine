#pragma once

#include "core.h"

class ARenderable;

class ENGINE_CLASS ARenderer
{
public:
    ARenderer();
    virtual ~ARenderer();

    virtual void Initialize();

    virtual void Draw(ARenderable* sprite) = 0;
};


#include <SDL2/SDL.h>
#include "sprite.h"
#include "texture.h"

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