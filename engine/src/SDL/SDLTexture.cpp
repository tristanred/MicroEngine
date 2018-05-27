#include "SDL/SDLTexture.h"

#include "SDL/SDLRenderer.h"

SDLTexture::SDLTexture(ARenderer* renderer) : ATexture(renderer)
{
    this->Renderer = renderer;
    this->SdlRenderer = (SDLRenderer*)renderer;

    this->surf = NULL;
    this->tex = NULL;
}

SDLTexture::~SDLTexture()
{
    SDL_DestroyTexture(tex);
}

void SDLTexture::SetColor(uint32_t color)
{
    if(this->surf != NULL)
    {
        SDL_FillRect(this->surf, NULL, color);

        this->isDirty = true;
    }
}

void SDLTexture::SetSize(FSize size)
{
    ATexture::SetSize(size);

    SDL_FreeSurface(this->surf);
    this->surf = SDL_CreateRGBSurface(0, (int)floor(size.Width), (int)floor(size.Width), 32, 0, 0, 0, 0);

    this->isDirty = true;
}

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
        }
    }
}
