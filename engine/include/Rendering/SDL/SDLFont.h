#pragma once

#ifdef SUPPORT_SDL

class Asset;

#include <SDL_ttf.h>

#include "Rendering/AFont.h"
#include "core.h"

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
#endif