#pragma once

class Asset;

#include "core.h"
#include "AFont.h"

#include <SDL_ttf.h>

#define DefaultLoadedFontSize 22

class ENGINE_CLASS SDLFont : public AFont
{
public:
    SDLFont();
    ~SDLFont() override;
    
    TTF_Font* fontObject;
    
    void LoadFontFile(std::string path) override;
    
    void LoadFontFile(Asset* asset) override;
};