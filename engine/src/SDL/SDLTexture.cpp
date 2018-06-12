#include "SDL/SDLTexture.h"

#include "SDL/SDLRenderer.h"

#include <SDL_image.h>
#include <cmath>

SDLTexture::SDLTexture(ARenderer* renderer) : ATexture(renderer)
{
    LogTrace("SDLTexture::SDLTexture");

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
    LogTrace("SDLTexture::~SDLTexture");

    SDL_DestroyTexture(tex);
}

void SDLTexture::SetSolidColor(FSize size, uint32_t color)
{
    if (this->surf != NULL)
    {
        SDL_free(this->surf);
    }

    this->textureSize = size;
    this->surf = SDL_CreateRGBSurface(0, (int)size.Width, (int)size.Height, 32, 0, 0, 0, 0);
    SDL_FillRect(surf, NULL, color);

    isDirty = true;
}

void SDLTexture::LoadFromFile(const char* filepath)
{
    if (this->surf != NULL)
    {
        SDL_free(this->surf);
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

