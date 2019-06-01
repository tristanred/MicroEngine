#if SUPPORT_COCOA == 1

#include "Cocoa/CocoaText.h"

CocoaText::CocoaText(ARenderer* renderer)
    : AText(renderer)
{

}

CocoaText::~CocoaText()
{

}

std::string* CocoaText::GetText()
{
    return new std::string("");
}

void CocoaText::SetText(std::string text)
{

}

AFont* CocoaText::GetFont()
{
    return NULL;
}

void CocoaText::SetFont(AFont* font)
{

}

int CocoaText::GetCharacterSize()
{
    return 0;
}

void CocoaText::SetCharacterSize(int size)
{

}

TextStyle CocoaText::GetStyle()
{
    return TextStyle::TEXT_STYLE_REGULAR;
}

void CocoaText::SetStyle(TextStyle style)
{

}

uint32_t CocoaText::GetColor()
{
    return 0;
}

void CocoaText::SetColor(uint32_t color)
{

}

void CocoaText::RefreshTexture()
{

}
#endif
