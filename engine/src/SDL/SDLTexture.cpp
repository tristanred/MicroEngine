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

    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    this->surf = SDL_CreateRGBSurface(0, (int)floor(size.Width), (int)floor(size.Width), 32, rmask, gmask, bmask, amask);

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
