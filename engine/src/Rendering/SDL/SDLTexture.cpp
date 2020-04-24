#ifdef SUPPORT_SDL

#include "Rendering/SDL/SDLTexture.h"

#include <SDL_image.h>

#include <cmath>

#include "GameEngine.h"
#include "Rendering/SDL/SDLRenderer.h"

SDLTexture::SDLTexture(ARenderer* renderer) : ATexture(renderer)
{
    this->Renderer = renderer;
    this->SdlRenderer = (SDLRenderer*)renderer;

    this->surf = NULL;
    this->tex = NULL;

    textureSize = FSize(0, 0);
}

SDLTexture::SDLTexture(ARenderer* renderer, SDL_Surface* fromSurface)
    : SDLTexture(renderer)
{
    this->surf = fromSurface;
    this->tex = this->SdlRenderer->BuildTexture(fromSurface);

    this->textureSize = FSize((float)fromSurface->w, (float)fromSurface->h);
    isDirty = false;
}

SDLTexture::~SDLTexture()
{
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}

void SDLTexture::SetSize(FSize size)
{
    // If we try to change the texture size and we are still at size 0, we can
    // change the size without rescaling the surface.
    // TODO : Special exception, not the best option but this is the only way
    // in some situation to set the initial size of the texture.
    if(this->textureSize.Zero())
    {
        this->textureSize = size;
        return;
    }

    // Case should be covered with a 0 texture size
    assert(this->surf != NULL);

    /*
     * Calling SetSize is a destructive action. We create a new surface,
     * do a scaled blit from the current to the new one and destroy the old
     * surface data.
     */
    SDL_Surface* newSurface = SDL_CreateRGBSurface(
        0, (int)size.Width, (int)size.Height, 32, rmask, gmask, bmask, amask);

    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = (int)this->textureSize.Width;
    srcRect.h = (int)this->textureSize.Height;

    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = (int)size.Width;
    destRect.h = (int)size.Height;
    int res = SDL_BlitScaled(this->surf, &srcRect, newSurface, &destRect);

    if(res != 0)
    {
        const char* errstring = SDL_GetError();
        LogError(errstring);

        return;
    }

    if(this->tex != NULL)
    {
        SDL_DestroyTexture(this->tex);
    }

    SDL_FreeSurface(this->surf);
    this->surf = newSurface;
    this->isDirty = true;

    this->textureSize = size;
}

void SDLTexture::SetSolidColor(FSize size, uint32_t color)
{
    if(this->surf != NULL)
    {
        SDL_FreeSurface(this->surf);
    }

    this->textureSize = size;
    this->surf = SDL_CreateRGBSurface(0, (int)size.Width, (int)size.Height, 32,
                                      rmask, gmask, bmask, amask);
    SDL_FillRect(surf, NULL, color);

    isDirty = true;
}

void SDLTexture::LoadFromFile(const char* filepath)
{
    if(this->surf != NULL)
    {
        SDL_FreeSurface(this->surf);
    }

    this->surf = IMG_Load(filepath);

    if(this->surf == NULL)
    {
        LogError("Unable to open the file texture");

        return;
    }

    if(this->surf->format->BitsPerPixel != 32)
    {
        LogWarning(
            "Surface format is %c bpp instead of 32. Recommends to convert the "
            "image.",
            this->surf->format->BitsPerPixel);
    }

    loadedTexturePath = filepath;

    this->textureSize = FSize((float)this->surf->w, (float)this->surf->h);

    isDirty = true;
}

void SDLTexture::FillColor(uint32_t color)
{
    if(this->surf != NULL)
    {
        loadedTexturePath = NULL;

        SDL_FillRect(this->surf, NULL, color);

        this->isDirty = true;
    }
}

void SDLTexture::StrokeRect(FRectangle rect, uint32_t size, uint32_t color)
{
    SDL_Renderer* rendy = SDL_CreateSoftwareRenderer(this->surf);

    // Parameter format is RGBA
    uint8_t r = (color & 0xFF000000) >> 24;
    uint8_t g = (color & 0x00FF0000) >> 16;
    uint8_t b = (color & 0x0000FF00) >> 8;
    uint8_t a = (color & 0x000000FF);
    SDL_SetRenderDrawColor(rendy, r, g, b, a);
    SDL_SetRenderDrawBlendMode(rendy, SDL_BLENDMODE_BLEND);

    for(uint32_t i = 0; i < size; i++)
    {
        SDL_Rect r;
        r.x = (int)rect.X + i;
        r.y = (int)rect.Y + i;
        r.w = (int)rect.Width - (i * 2);
        r.h = (int)rect.Height - (i * 2);
        SDL_RenderDrawRect(rendy, &r);
    }

    SDL_DestroyRenderer(rendy);

    this->isDirty = true;
}

void SDLTexture::FillRect(FRectangle rect, uint32_t color)
{
    SDL_Renderer* rendy = SDL_CreateSoftwareRenderer(this->surf);
    uint8_t r = (color & 0xFF000000) >> 24;
    uint8_t g = (color & 0x00FF0000) >> 16;
    uint8_t b = (color & 0x0000FF00) >> 8;
    uint8_t a = (color & 0x000000FF);
    SDL_SetRenderDrawColor(rendy, r, g, b, a);
    SDL_SetRenderDrawBlendMode(rendy, SDL_BLENDMODE_BLEND);

    SDL_Rect dest;
    dest.w = (int)rect.Width;
    dest.h = (int)rect.Height;
    dest.x = (int)rect.X;
    dest.y = (int)rect.Y;

    SDL_RenderFillRect(rendy, &dest);
    SDL_DestroyRenderer(rendy);

    this->isDirty = true;
}

void SDLTexture::DrawLine(FPosition pos1,
                          FPosition pos2,
                          uint32_t color,
                          uint32_t size)
{
    SDL_Renderer* rendy = SDL_CreateSoftwareRenderer(this->surf);
    uint8_t r = (color & 0xFF000000) >> 24;
    uint8_t g = (color & 0x00FF0000) >> 16;
    uint8_t b = (color & 0x0000FF00) >> 8;
    uint8_t a = (color & 0x000000FF);
    SDL_SetRenderDrawColor(rendy, r, g, b, a);
    SDL_SetRenderDrawBlendMode(rendy, SDL_BLENDMODE_BLEND);

    SDL_RenderDrawLine(rendy, (int)pos1.X, (int)pos1.Y, (int)pos2.X,
                       (int)pos2.Y);
    SDL_DestroyRenderer(rendy);

    this->isDirty = true;
}

void SDLTexture::FreeTextureMemory()
{
    if(surf != NULL)
    {
        SDL_FreeSurface(surf);
    }
}

void SDLTexture::ReloadTexture()
{
    if(this->loadedTexturePath != NULL)
    {
        this->LoadFromFile(loadedTexturePath);
    }
}

ATexture* SDLTexture::GetSubTexture(int x, int y, int width, int height)
{
    SDL_Surface* subSurface =
        SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);

    Uint32 color = SDL_MapRGBA(subSurface->format, 255, 255, 255, 0);

    SDL_FillRect(subSurface, NULL, color);

    SDL_Rect sourceRect = SDL_Rect();
    sourceRect.x = x;
    sourceRect.y = y;
    sourceRect.w = width;
    sourceRect.h = height;

    int res = SDL_BlitSurface(this->surf, &sourceRect, subSurface, NULL);

    if(res != 0)
    {
        const char* errstring = SDL_GetError();
        LogError(errstring);

        return NULL;  // TODO Free stuff
    }

    SDLTexture* newTexture = new SDLTexture(this->Renderer, subSurface);

    return newTexture;
}

void SDLTexture::CopyFrom(ATexture* other,
                          FPosition sourcePos,
                          FSize sourceSize,
                          FPosition destPos)
{
    SDLTexture* otherTexture = (SDLTexture*)other;

    FSize currentTextureNewSize;
    if(sourceSize.Zero())
    {
        currentTextureNewSize = otherTexture->GetSize();
    }
    else
    {
        currentTextureNewSize = sourceSize;
    }

    this->SetSize(currentTextureNewSize);

    SDL_Rect sourceRect;
    sourceRect.x = (int)sourcePos.X;
    sourceRect.y = (int)sourcePos.Y;
    sourceRect.h = (int)sourceSize.Height;
    sourceRect.w = (int)sourceSize.Width;

    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = (int)currentTextureNewSize.Width;
    destRect.h = (int)currentTextureNewSize.Height;
    int res =
        SDL_BlitSurface(otherTexture->surf, &sourceRect, this->surf, &destRect);

    if(res != 0)
    {
        const char* errstring = SDL_GetError();
        LogError(errstring);

        return;
    }

    this->isDirty = true;
}

//************************************
// Method:    RefreshSDLTexture
// FullName:  SDLTexture::RefreshSDLTexture
// Access:    public
// Returns:   void
// Qualifier: Recreates the SDL_Texture if the SDL_Surface was changed.
//************************************
void SDLTexture::RefreshSDLTexture()
{
    if(isDirty)
    {
        if(this->surf != NULL)
        {
            if(this->tex != NULL)
            {
                SDL_DestroyTexture(this->tex);
            }

            SDL_Texture* updated = this->SdlRenderer->BuildTexture(this->surf);
            this->tex = updated;

            isDirty = false;
        }
    }
}

#endif