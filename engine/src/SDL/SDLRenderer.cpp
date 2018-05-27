#include "SDL/SDLRenderer.h"

#include <cstdio>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "SDL/SDLSprite.h"
#include "SDL/SDLTexture.h"

SDLRenderer::SDLRenderer() : ARenderer()
{
    LogTrace("SDLRenderer::SDLRenderer");

    this->gameRenderer = NULL;
    this->mainWindow = NULL;
}

SDLRenderer::~SDLRenderer()
{
    LogTrace("SDLRenderer::~SDLRenderer");
}

void SDLRenderer::Initialize()
{
    LogTrace("SDLRenderer::Initialize");

    int res = 0;
    const char* errorString;
    char logMessage[1024];

    res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if (res != 0)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to init SDL with error %s\n", errorString);

        sprintf(logMessage, "Error in SDL_Init : %s", errorString);
        LogError(logMessage);

        return;
    }

    this->mainWindow = SDL_CreateWindow("Window Title !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    if (mainWindow == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create the window SDL with error %s\n", errorString);

        sprintf(logMessage, "Error in SDL_CreateWindow : %s", errorString);
        LogError(logMessage);

        return;
    }

    this->gameRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gameRenderer == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create the Accelerated Renderer with error %s\n", errorString);

        sprintf(logMessage, "Error in SDL_CreateRenderer : %s", errorString);
        LogError(logMessage);

        return;
    }

    // TODO SDL_Image
    res = IMG_Init(IMG_INIT_PNG);

    if (res == 0)
    {
        errorString = IMG_GetError();
        fprintf(stderr, "Unable to create the load SDL_Image with error %s\n", errorString);

        sprintf(logMessage, "Error in IMG_Init : %s", errorString);
        LogError(logMessage);

        return;
    }

    res = SDL_RenderSetScale(gameRenderer, 1, 1);

    if (res != 0)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to scale by %f,%f with error %s\n", 1.0, 1.0, errorString);

        sprintf(logMessage, "Error in SDL_RenderSetScale : %s", errorString);
        LogError(logMessage);

        return;
    }

    // TODO INIT TTF
    res = TTF_Init();

    if (res != 0)
    {
        errorString = TTF_GetError();
        fprintf(stderr, "Unable to init SDL_TTF with error %s\n", errorString);

        sprintf(logMessage, "Error in TTF_Init : %s", errorString);
        LogError(logMessage);

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
}

SDL_Texture* SDLRenderer::BuildTexture(SDL_Surface* surface)
{
    LogTrace("SDLRenderer::BuildTexture");

    SDL_Texture* result = SDL_CreateTextureFromSurface(this->gameRenderer, surface);

    return result;
}

ATexture *SDLRenderer::CreateTexture()
{
    LogTrace("SDLRenderer::CreateTexture");

    SDLTexture* result = new SDLTexture(this);

    return result;
}

void SDLRenderer::BeginDraw()
{
    ARenderer::BeginDraw();

    SDL_SetRenderDrawColor(gameRenderer, 100, 149, 237, 255);

    SDL_RenderClear(gameRenderer);
}

void SDLRenderer::EndDraw()
{
    ARenderer::EndDraw();

    SDL_RenderPresent(gameRenderer);
}

