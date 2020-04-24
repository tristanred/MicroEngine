#pragma once

#ifdef SUPPORT_SDL

class SDLRenderer;
class GameEngine;

#include <stdint.h>
#include <string.h>

#include <string>

#include "Rendering/AFont.h"
#include "Rendering/AText.h"
#include "Rendering/RenderableObject.h"
#include "Rendering/SDL/SDLFont.h"
#include "core.h"

class ENGINE_CLASS SDLText : public AText
{
public:
    SDLText(GameEngine* engine);
    ~SDLText();

    std::string* GetText() override;
    void SetText(std::string text) override;

    AFont* GetFont() override;
    void SetFont(AFont* font) override;

    int GetCharacterSize() override;
    void SetCharacterSize(int size) override;

    TextStyle GetStyle() override;
    void SetStyle(TextStyle style = TEXT_STYLE_REGULAR) override;

    uint32_t GetColor() override;
    void SetColor(uint32_t color) override;

    void RefreshTexture();

private:
    bool dirtyFlag;
    void IsDirty();

    SDLRenderer* sdlRenderer;
    std::string* currentText;

    SDLFont* sdlFont;

    // Text style
    int textSize;
    uint32_t foregroundColor;
    TextStyle style;
};
#endif