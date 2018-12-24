#include "SDL/SDLTexture.h"

#include "SDL/SDLRenderer.h"

#include <SDL_image.h>
#include <cmath>

SDLTexture::SDLTexture(ARenderer* renderer) : ATexture(renderer)
{
    this->Renderer = renderer;
    this->SdlRenderer = (SDLRenderer*)renderer;

    this->surf = NULL;
    this->tex = NULL;

    TextureSize = FSize(0, 0);
}

SDLTexture::SDLTexture(ARenderer* renderer, SDL_Surface* fromSurface) : SDLTexture(renderer)
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

void SDLTexture::SetSolidColor(FSize size, uint32_t color)
{
    if (this->surf != NULL)
    {
        SDL_FreeSurface(this->surf);
    }

    this->textureSize = size;
    this->surf = SDL_CreateRGBSurface(0, (int)size.Width, (int)size.Height, 32, rmask, gmask, bmask, amask);
    SDL_FillRect(surf, NULL, color);

    isDirty = true;
}

void SDLTexture::LoadFromFile(const char* filepath)
{
    if (this->surf != NULL)
    {
        SDL_FreeSurface(this->surf);
    }

    this->surf = IMG_Load(filepath);

    if (this->surf == NULL)
    {
        LogError("Unable to open the file texture");

        return;
    }

    loadedTexturePath = filepath;

    this->textureSize = FSize((float)this->surf->w, (float)this->surf->h);

    isDirty = true;
}

void SDLTexture::FillColor(uint32_t color)
{
    LogTrace("SDLTexture::SetColor");

    if(this->surf != NULL)
    {
        //SDL_FreeSurface(surf);
        
        loadedTexturePath = NULL;

        SDL_FillRect(this->surf, NULL, color);

        this->isDirty = true;
    }
}

void SDLTexture::FreeTextureMemory()
{
    if (surf != NULL)
    {
        SDL_FreeSurface(surf);
    }
}

void SDLTexture::ReloadTexture()
{
    if (this->loadedTexturePath != NULL)
    {
        this->LoadFromFile(loadedTexturePath);
    }
}

ATexture* SDLTexture::GetSubTexture(int x, int y, int width, int height)
{
    SDL_Surface* subSurface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
    
    Uint32 color = SDL_MapRGBA(subSurface->format, 255, 255, 255, 255);
    
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
        
        return NULL; // TODO Free stuff
    }
    
    SDLTexture* newTexture = new SDLTexture(this->Renderer, subSurface);
    
    return newTexture;
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

