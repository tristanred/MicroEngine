#ifdef SUPPORT_SDL

#include "Rendering/SDL/SDLFont.h"

#include "Asset.h"

SDLFont::SDLFont()
{
    fontObject = NULL;
}

SDLFont::~SDLFont()
{
    if(fontObject)
        SDL_free(fontObject);
}

void SDLFont::LoadFontFile(std::string path)
{
    fontObject = TTF_OpenFont(path.c_str(), DefaultLoadedFontSize);

    if(fontObject == NULL)
    {
        const char* errorString = TTF_GetError();
        LogError(errorString);
    }
}

void SDLFont::LoadFontFile(Asset* asset)
{
    SDL_RWops* rw = SDL_RWFromMem(asset->GetData(), (int)asset->size);

    // Opting to TRUE so the openFont closes the 'rw' when done.
    // Hoping it does clear Asset's data channels
    fontObject = TTF_OpenFontRW(rw, true, DefaultLoadedFontSize);

    if(fontObject == NULL)
    {
        const char* errorString = TTF_GetError();
        LogError(errorString);
    }
}
#endif