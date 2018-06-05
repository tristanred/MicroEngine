#include "SDL/SDLFont.h"

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
    fontObject = TTF_OpenFont(path.c_str(), 22);
    
    if(fontObject == NULL)
    {
        const char* errorString = TTF_GetError();
        LogError(errorString);
    }
}