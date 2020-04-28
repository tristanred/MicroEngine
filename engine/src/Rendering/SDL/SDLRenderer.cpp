#ifdef SUPPORT_SDL

#include "Rendering/SDL/SDLRenderer.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <libtech/filecache.h>

#include <cstdio>
#include <string.h>
#include <string>

#include "Config/IConfigProvider.h"
#include "Rendering/SDL/SDLTexture.h"
#include "Viewport.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
const Uint32 rmask = 0xff000000;
const Uint32 gmask = 0x00ff0000;
const Uint32 bmask = 0x0000ff00;
const Uint32 amask = 0x000000ff;
#else
const Uint32 rmask = 0x000000ff;
const Uint32 gmask = 0x0000ff00;
const Uint32 bmask = 0x00ff0000;
const Uint32 amask = 0xff000000;
#endif

SDLRenderer::SDLRenderer() : ARenderer()
{
    LogTrace("SDLRenderer::SDLRenderer");

    this->gameRenderer = NULL;
    this->mainWindow = NULL;
    this->screenshotRequested = false;
}

SDLRenderer::~SDLRenderer()
{
    LogTrace("SDLRenderer::~SDLRenderer");
}

bool SDLRenderer::Initialize()
{
    LogTrace("SDLRenderer::Initialize");

    RendererParameters defaults;
    strcpy(defaults.window_title, "Window titlez !");

    defaults.window_width = 800;
    defaults.window_height = 600;
    defaults.renderScaleX = 1;
    defaults.renderScaleY = 1;

    return this->Initialize(&defaults);
}

bool SDLRenderer::Initialize(IConfigProvider* config)
{
    LogTrace("SDLRenderer::Initialize with ConfigFile");

    if(config == NULL)
    {
        LogError("Config file is NULL. Loading backup defaults.");

        return this->Initialize();
    }

    RendererParameters defaults;

    std::string configValueSafe =
        config->GetConfigValueSafe("default_window_name", "Window Titlez !");
    strcpy(defaults.window_title, configValueSafe.c_str());

    std::string wWidth =
        config->GetConfigValueSafe("default_engine_width", "800");
    defaults.window_width = atoi(wWidth.c_str());

    std::string wHeight =
        config->GetConfigValueSafe("default_engine_height", "600");
    defaults.window_height = atoi(wHeight.c_str());

    std::string scaleX =
        config->GetConfigValueSafe("default_engine_scaleX", "1");
    defaults.renderScaleX = stof(scaleX.c_str());

    std::string scaleY =
        config->GetConfigValueSafe("default_engine_scaleY", "1");
    defaults.renderScaleY = stof(scaleY.c_str());

    return this->Initialize(&defaults);
}

bool SDLRenderer::Initialize(RendererParameters* params)
{
    LogTrace("SDLRenderer::Initialize with RendererParameters");

    LogTrace("Renderer Parameters : ");
    LogTrace("    Window Title = %s", params->window_title);
    LogTrace("    Window Width = %d", params->window_width);
    LogTrace("    Window Height = %d", params->window_height);
    LogTrace("    Window RenderScaleX = %f", params->renderScaleX);
    LogTrace("    Window RenderScaleY = %f", params->renderScaleY);

    int res = 0;
    const char* errorString;

    LogTrace("Initializing SDL with subsystem Video and Audio.");
    res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if(res != 0)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to init SDL with error %s\n", errorString);

        LogError("Error in SDL_Init : %s", errorString);

        return false;
    }

    this->mainWindow = SDL_CreateWindow(
        params->window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        params->window_width, params->window_height, 0);

    if(mainWindow == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to create the window SDL with error %s\n",
                errorString);

        LogError("Error in SDL_CreateWindow : %s", errorString);

        return false;
    }

    this->gameRenderer =
        SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);

    if(gameRenderer == NULL)
    {
        errorString = SDL_GetError();
        fprintf(stderr,
                "Unable to create the Accelerated Renderer with error %s\n",
                errorString);

        LogError("Error in SDL_CreateRenderer : %s", errorString);

        return false;
    }

    // TODO SDL_Image
    res = IMG_Init(IMG_INIT_PNG);

    if(res == 0)
    {
        errorString = IMG_GetError();
        fprintf(stderr, "Unable to create the load SDL_Image with error %s\n",
                errorString);

        LogError("Error in IMG_Init : %s", errorString);

        return false;
    }

    res = SDL_RenderSetScale(gameRenderer, params->renderScaleX,
                             params->renderScaleY);

    if(res != 0)
    {
        errorString = SDL_GetError();
        fprintf(stderr, "Unable to scale by %f,%f with error %s\n", 1.0, 1.0,
                errorString);

        LogError("Error in SDL_RenderSetScale : %s", errorString);

        return false;
    }

    // TODO INIT TTF
    res = TTF_Init();

    if(res != 0)
    {
        errorString = TTF_GetError();
        fprintf(stderr, "Unable to init SDL_TTF with error %s\n", errorString);

        LogError("Error in TTF_Init : %s", errorString);

        return false;
    }

    SDL_ShowWindow(mainWindow);

    return true;
}

void SDLRenderer::Shutdown()
{
    LogTrace("SDLRenderer::Shutdown");

    SDL_Quit();
}

void SDLRenderer::Draw(RenderableObject* renderObject)
{
    if(renderObject->IsVisible() == false)
        return;

    renderObject->OnPreDraw();

    SDLTexture* tex = (SDLTexture*)renderObject->GetTexture();

    if(tex == NULL)
        return;

    SDL_Rect dest;
    dest.w = (int)renderObject->GetSize().Width;
    dest.h = (int)renderObject->GetSize().Height;
    dest.x = (int)renderObject->GetPosition().X;
    dest.y = (int)renderObject->GetPosition().Y;

    if(renderObject->GetPositionSystem() == VIEWPORT_RELATIVE)
    {
        dest.x -= (int)this->RenderViewport->CurrentView.X;
        dest.y -= (int)this->RenderViewport->CurrentView.Y;
    }

    tex->RefreshSDLTexture();  // Refresh the texture if needed.

    int res = SDL_RenderCopy(gameRenderer, tex->tex, NULL, &dest);
    if(res == -1)
    {
        const char* msg = SDL_GetError();
        LogError(msg);
    }

    renderObject->OnPostDraw();
}

void SDLRenderer::DrawTexture(ATexture* texture, float posX, float posY)
{
    SDLTexture* tex = (SDLTexture*)texture;

    assert(texture != NULL);

    SDL_Rect dest;
    dest.w = (int)tex->GetSize().Width;
    dest.h = (int)tex->GetSize().Height;
    dest.x = (int)posX;
    dest.y = (int)posY;

    tex->RefreshSDLTexture();

    int res = SDL_RenderCopy(gameRenderer, tex->tex, NULL, &dest);
    if(res == -1)
    {
        const char* msg = SDL_GetError();
        LogError(msg);
    }
}

void SDLRenderer::DrawTexture(ATexture* texture,
                              float posX,
                              float posY,
                              struct TextureDrawOptions* opts)
{
    assert(opts != NULL);

    float offsetPosX = posX;
    float offsetPosY = posY;

    if(opts->PosSystem == VIEWPORT_RELATIVE)
    {
        offsetPosX -= this->RenderViewport->CurrentView.X;
        offsetPosY -= this->RenderViewport->CurrentView.Y;
    }

    this->DrawTexture(texture, offsetPosX, offsetPosY);
}

SDL_Texture* SDLRenderer::BuildTexture(SDL_Surface* surface)
{
    assert(surface != NULL);

    SDL_Texture* result =
        SDL_CreateTextureFromSurface(this->gameRenderer, surface);

    return result;
}

FSize SDLRenderer::GetWindowSize()
{
    int x = 0;
    int y = 0;
    SDL_GetWindowSize(mainWindow, &x, &y);

    return FSize((float)x, (float)y);
}

ATexture* SDLRenderer::CreateTexture()
{
    LogTrace("SDLRenderer::CreateTexture");

    SDLTexture* result = new SDLTexture(this);

    return result;
}

ATexture* SDLRenderer::CreateTexture(void* data, int length)
{
    LogTrace("SDLRenderer::CreateTexture(filepath)");

    SDLTexture* result = new SDLTexture(this);

    SDL_RWops* stream = SDL_RWFromMem(data, length);

    SDL_Surface* surface = IMG_Load_RW(stream, false);

    // Delete the stream ?

    result->surf = surface;

    if(result->surf == NULL)
    {
        LogError("Unable to load texture file.");

        delete(result);

        return NULL;
    }

    if(surface->format->BitsPerPixel != 32)
    {
        LogWarning(
            "Surface format is %c bpp instead of 32. Recommends to convert the "
            "image.",
            surface->format->BitsPerPixel);
    }

    result->SetSize(FSize((float)result->surf->w, (float)result->surf->h));

    return result;
}

void SDLRenderer::DeleteTexture(ATexture* texture)
{
    SDLTexture* tex = (SDLTexture*)texture;

    delete(tex);
}

void SDLRenderer::BeginDraw()
{
    // Clear screen using the color Cornflower Blue, the best color.
    SDL_SetRenderDrawColor(gameRenderer, 100, 149, 237, 255);

    SDL_RenderClear(gameRenderer);
}

void SDLRenderer::EndDraw()
{
    SDL_RenderPresent(gameRenderer);

    if(this->screenshotRequested)
    {
        FSize screenSize = this->GetWindowSize();

        SDL_Surface* surf = SDL_CreateRGBSurface(0, (int)screenSize.Width,
                                                 (int)screenSize.Height, 32,
                                                 rmask, gmask, bmask, amask);

        int res =
            SDL_RenderReadPixels(gameRenderer, NULL, SDL_PIXELFORMAT_ABGR8888,
                                 surf->pixels, surf->pitch);

        if(res == 0)
        {
            IMG_SavePNG(surf, "out.png");
        }
        else
        {
            const char* msg = SDL_GetError();
            LogError(msg);
        }

        SDL_FreeSurface(surf);

        this->screenshotRequested = false;
    }
}

void SDLRenderer::ScreenshotNextFrame()
{
    this->screenshotRequested = true;
}

void SDLRenderer::SaveToFile(RenderableObject* object, const char* path)
{
    SDL_Texture* tex = SDL_CreateTexture(
        gameRenderer, SDL_PIXELFORMAT_ABGR8888,
        SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET,
        (int)object->GetSize().Width, (int)object->GetSize().Height);
    SDL_SetRenderTarget(gameRenderer, tex);

    this->DrawHierarchy(object);
    SDL_Surface* surf = SDL_CreateRGBSurface(0, (int)object->GetSize().Width,
                                             (int)object->GetSize().Height, 32,
                                             rmask, gmask, bmask, amask);

    int res = SDL_RenderReadPixels(gameRenderer, NULL, SDL_PIXELFORMAT_ABGR8888,
                                   surf->pixels, surf->pitch);

    if(res == 0)
    {
        IMG_SavePNG(surf, path);
    }

    SDL_FreeSurface(surf);
    SDL_SetRenderTarget(gameRenderer, NULL);
    SDL_DestroyTexture(tex);
}

void SDLRenderer::DrawHierarchy(RenderableObject* object)
{
    if(object == NULL)
    {
        return;
    }

    this->Draw(object);
    auto children = object->GetChildren();
    for(int i = 0; i < children->Count(); i++)
    {
        this->DrawHierarchy(children->Get(i));
    }
}
#endif