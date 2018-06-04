#include "SDL/SDLRenderer.h"

#include <cstdio>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "SDL/SDLSprite.h"
#include "SDL/SDLTexture.h"
#include "ConfigFile.h"

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

    RendererParameters defaults;

    const char* defaultWindowTitle ="Window titlez !";
    defaults.window_title = new char[strlen(defaultWindowTitle)];
    strcpy(defaults.window_title, defaultWindowTitle);

    defaults.window_width = 800;
    defaults.window_height = 600;
    defaults.renderScaleX = 1;
    defaults.renderScaleY = 1;

    this->Initialize(&defaults);
}

void SDLRenderer::Initialize(ConfigFile* config)
{
    LogTrace("SDLRenderer::Initialize with ConfigFile");

    RendererParameters defaults;

    const char* windowTitle = config->GetConfigValueSafe("default_window_name", "Window Titlez !").c_str();
    defaults.window_title = new char[strlen(windowTitle)];
    strcpy(defaults.window_title, windowTitle);

    std::string wWidth= config->GetConfigValueSafe("default_engine_width", "800");
    defaults.window_width = atoi(wWidth.c_str());

    std::string wHeight = config->GetConfigValueSafe("default_engine_height", "600");
    defaults.window_height = atoi(wHeight.c_str());

    std::string scaleX = config->GetConfigValueSafe("default_engine_scaleX", "2");
    defaults.renderScaleX = stof(scaleX.c_str());

    std::string scaleY = config->GetConfigValueSafe("default_engine_scaleY", "3");
    defaults.renderScaleY = stof(scaleY.c_str());

    this->Initialize(&defaults);
}

void SDLRenderer::Initialize(RendererParameters* params)
{
    LogTrace("SDLRenderer::Initialize with RendererParameters");

    int res = 0;
    const char* errorString;
    char logMessage[1024];

    res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if(res != 0)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to init SDL with error %s\n", errorString);

        sprintf(logMessage, "Error in SDL_Init : %s", errorString);
        LogError(logMessage);

        return;
    }

    this->mainWindow = SDL_CreateWindow(params->window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, params->window_width, params->window_height, 0);

    if(mainWindow == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create the window SDL with error %s\n", errorString);

        sprintf(logMessage, "Error in SDL_CreateWindow : %s", errorString);
        LogError(logMessage);

        return;
    }

    this->gameRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

    if(gameRenderer == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create the Accelerated Renderer with error %s\n", errorString);

        sprintf(logMessage, "Error in SDL_CreateRenderer : %s", errorString);
        LogError(logMessage);

        return;
    }

    // TODO SDL_Image
    res = IMG_Init(IMG_INIT_PNG);

    if(res == 0)
    {
        errorString = IMG_GetError();
        fprintf(stderr, "Unable to create the load SDL_Image with error %s\n", errorString);

        sprintf(logMessage, "Error in IMG_Init : %s", errorString);
        LogError(logMessage);

        return;
    }

    res = SDL_RenderSetScale(gameRenderer, params->renderScaleX, params->renderScaleY);

    if(res != 0)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to scale by %f,%f with error %s\n", 1.0, 1.0, errorString);

        sprintf(logMessage, "Error in SDL_RenderSetScale : %s", errorString);
        LogError(logMessage);

        return;
    }

    // TODO INIT TTF
    res = TTF_Init();

    if(res != 0)
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

