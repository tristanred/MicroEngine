#pragma once

class GameEngine;
class AFont;

#include <stdint.h>
#include <string.h>

#include <string>

#include "Rendering/AText.h"
#include "core.h"


class ENGINE_CLASS NullText : public AText
{
public:
    NullText(GameEngine* engine);
    ~NullText();

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

private:
    std::string* text;
};