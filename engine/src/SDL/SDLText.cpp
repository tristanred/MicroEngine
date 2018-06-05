#include "SDL/SDLText.h"

SDLText::SDLText(ARenderer* renderer) : AText(renderer)
{
    TextFont = NULL;
    sdlFont = NULL;
    currentText = "";
    textSize = 12;
    style = TEXT_STYLE_REGULAR;
}

SDLText::~SDLText()
{
    if (sdlFont != NULL)
        delete(sdlFont);
}

std::string SDLText::GetText()
{
    return currentText;
}

void SDLText::SetText(std::string text)
{
    currentText = text;
}

AFont* SDLText::GetFont()
{
    return sdlFont;
}

void SDLText::SetFont(AFont* font)
{
    this->TextFont = font;
    this->sdlFont = dynamic_cast<SDLFont*>(font);

    if (this->sdlFont == NULL)
    {
        LogError("Invalid cast to an SDLFont");
    }
}

int SDLText::GetCharacterSize()
{
    return textSize;
}

void SDLText::SetCharacterSize(int size)
{
    textSize = size;
}

TextStyle SDLText::GetStyle()
{
    return style;
}

void SDLText::SetStyle(TextStyle style /*= TEXT_STYLE_REGULAR*/)
{
    style = style;
}

uint32_t SDLText::GetColor()
{
    return foregroundColor;
}

void SDLText::SetColor(uint32_t color)
{
    foregroundColor = color;
}

ATexture* SDLText::GetTexture()
{
    return NULL;
}

void SDLText::SetTexture(ATexture* texture)
{
}

void SDLText::RefreshTexture()
{
    if (this->sdlFont == NULL || this->textSize <= 0)
        return;

    SDL_Color color = { 0,0,0,0 };
    color.a = (this->foregroundColor & 0xFF000000) >> 24;
    color.r = (this->foregroundColor & 0x00FF0000) >> 16;
    color.g = (this->foregroundColor) & 0x0000FF00 >> 8;
    color.b = (this->foregroundColor) & 0x000000FF;
    SDL_Surface* renderedSurface = TTF_RenderText_Solid(this->sdlFont->fontObject, currentText.c_str(), color);

    if (renderedSurface == NULL)
    {
        const char* errorString = TTF_GetError();
        LogError(errorString);

        return;
    }

    this->SetSize(FSize(renderedSurface->w, renderedSurface->h));

    

}
