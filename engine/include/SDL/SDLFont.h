#pragma once

#include "core.h"
#include "AFont.h"

#include <SDL_ttf.h>

class ENGINE_CLASS SDLFont : public AFont
{
public:
    SDLFont();
    ~SDLFont();
    
    TTF_Font* fontObject;
    
    void LoadFontFile(std::string path) override;
};