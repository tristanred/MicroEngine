#include "texture.h"

#include "renderer.h"

SDLTexture::SDLTexture(ARenderer* renderer)
{
    this->Renderer = renderer;
    this->SdlRenderer = (SDLRenderer*)renderer;

    this->surf = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    
    SDL_FillRect(surf, NULL, 0x88444477);
    
    this->tex = this->SdlRenderer->BuildTexture(surf);
}

SDLTexture::~SDLTexture()
{
    SDL_DestroyTexture(tex);
}

ATexture::ATexture()
{

}

ATexture::~ATexture()
{

}
