#ifdef SUPPORT_SDL

#include "SDL/SDLText.h"

#include "SDL/SDLRenderer.h"
#include "SDL/SDLTexture.h"

SDLText::SDLText(ARenderer* renderer) : AText(renderer)
{
    sdlRenderer = (SDLRenderer*)renderer;
    TextFont = NULL;
    sdlFont = NULL;
    currentText = new std::string();
    textSize = 12;
    style = TEXT_STYLE_REGULAR;
    foregroundColor = 0xFFFFFFFF;
    dirtyFlag = false;
}

SDLText::~SDLText()
{
    if (sdlFont != NULL)
        delete(sdlFont);

    delete(currentText);
}

std::string* SDLText::GetText()
{
    return currentText;
}

void SDLText::SetText(std::string text)
{
    if (this->currentText->compare(text) != 0)
    {
        currentText->assign(text);

        RefreshTexture();
    }
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
    if (textSize != size)
    {
        textSize = size;

        RefreshTexture();
    }
}

TextStyle SDLText::GetStyle()
{
    return style;
}

void SDLText::SetStyle(TextStyle style /*= TEXT_STYLE_REGULAR*/)
{
    if (this->style != style)
    {
        this->style = style;

        RefreshTexture();
    }
}

uint32_t SDLText::GetColor()
{
    return foregroundColor;
}

void SDLText::SetColor(uint32_t color)
{
    if (this->foregroundColor != color)
    {
        foregroundColor = color;

        RefreshTexture();
    }
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
    SDL_Surface* renderedSurface = TTF_RenderText_Solid(this->sdlFont->fontObject, currentText->c_str(), color);

    if (renderedSurface == NULL)
    {
        const char* errorString = TTF_GetError();
        LogError(errorString);

        return;
    }

    this->SetSize(FSize((float)renderedSurface->w, (float)renderedSurface->h));

    SDLTexture* newTex = new SDLTexture(this->sdlRenderer, renderedSurface);

    this->SetTexture(newTex);
}
#endif