#include "Rendering/NullRenderer/NullText.h"

NullText::NullText(GameEngine* engine) : AText(engine)
{
    this->text = new std::string("");
}

NullText::~NullText() {}

std::string* NullText::GetText()
{
    return this->text;
}

void NullText::SetText(std::string text)
{
    *this->text = text;
}

AFont* NullText::GetFont()
{
    return this->TextFont;
}

void NullText::SetFont(AFont* font)
{
    this->TextFont = font;
}

int NullText::GetCharacterSize()
{
    return 12;
}

void NullText::SetCharacterSize(int size) {}

TextStyle NullText::GetStyle()
{
    return TextStyle::TEXT_STYLE_REGULAR;
}

void NullText::SetStyle(TextStyle style /*= TEXT_STYLE_REGULAR*/) {}

uint32_t NullText::GetColor()
{
    return 0xFFFFFFFF;
}

void NullText::SetColor(uint32_t color) {}