#pragma once

class AFont;
class ATexture;

#include <string>
#include <string.h>

#include "core.h"
#include "ARenderable.h"

enum TextStyle {
    TEXT_STYLE_REGULAR,
    TEXT_STYLE_BOLD,
    TEXT_STYLE_ITALIC
};

class ENGINE_CLASS AText : public ARenderable
{
public:
    AText(ARenderer* renderer);
    virtual ~AText();

    AFont* TextFont;
    
    virtual std::string* GetText() = 0;
    virtual void SetText(std::string text) = 0;
    
    virtual AFont* GetFont() = 0;
    virtual void SetFont(AFont* font) = 0;
    
    virtual int GetCharacterSize() = 0;
    virtual void SetCharacterSize(int size) = 0;

    virtual TextStyle GetStyle() = 0;
    virtual void SetStyle(TextStyle style = TEXT_STYLE_REGULAR) = 0;

    virtual uint32_t GetColor() = 0;
    virtual void SetColor(uint32_t color) = 0;
};