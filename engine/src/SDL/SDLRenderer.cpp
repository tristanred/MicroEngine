#include "SDL/SDLRenderer.h"

#include <cstdio>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "SDL/SDLSprite.h"
#include "SDL/SDLTexture.h"

SDLRenderer::SDLRenderer()
{
    this->gameRenderer = NULL;
    this->mainWindow = NULL;
}

SDLRenderer::~SDLRenderer()
{

}

void SDLRenderer::Initialize()
{
    int res = 0;
    const char* errorString;

    res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if (res != 0)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to init SDL with error %s\n", errorString);

        return;
    }

    this->mainWindow = SDL_CreateWindow("Window Title !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    if (mainWindow == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create the window SDL with error %s\n", errorString);

        return;
    }

    this->gameRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gameRenderer == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create the Accelerated Renderer with error %s\n", errorString);

        return;
    }

    // TODO SDL_Image
    res = IMG_Init(IMG_INIT_PNG);

    if (res == 0)
    {
        errorString = IMG_GetError();
        fprintf(stderr, "Unable to create the load SDL_Image with error %s\n", errorString);

        return;
    }

    res = SDL_RenderSetScale(gameRenderer, 1, 1);

    if (res != 0)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to scale by %f,%f with error %s\n", 1.0, 1.0, errorString);

        return;
    }

    // TODO INIT TTF
    res = TTF_Init();

    if (res != 0)
    {
        errorString = TTF_GetError();
        fprintf(stderr, "Unable to init SDL_TTF with error %s\n", errorString);

        return;
    }

    SDL_ShowWindow(mainWindow);
}

void SDLRenderer::Draw(ARenderable* sprite)
{
    SDLSprite* sdlSprite = (SDLSprite*)sprite;

    SDL_Rect dest;
    dest.w = (int)sdlSprite->GetSize().Width;
    dest.h = (int)sdlSprite->GetSize().Height;
    dest.x = (int)sdlSprite->GetPosition().X;
    dest.y = (int)sdlSprite->GetPosition().Y;

    SDLTexture* tex = (SDLTexture*)sdlSprite->GetTexture();

    tex->RefreshSDLTexture(); // Refresh the texture if needed.

    SDL_RenderCopy(gameRenderer, tex->tex, NULL, &dest);

    SDL_RenderPresent(gameRenderer);
}

SDL_Texture* SDLRenderer::BuildTexture(SDL_Surface* surface)
{
    SDL_Texture* result = SDL_CreateTextureFromSurface(this->gameRenderer, surface);

    return result;
}

ATexture *SDLRenderer::CreateTexture()
{
    SDLTexture* result = new SDLTexture(this);

    return result;
}
