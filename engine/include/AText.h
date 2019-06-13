#pragma once

class AFont;
class ATexture;
class GameEngine;

#include <string>
#include <string.h>

#include "core.h"
#include "RenderableObject.h"

/**
 * \brief Supported text styles.
 */
enum TextStyle {
    TEXT_STYLE_REGULAR,
    TEXT_STYLE_BOLD,
    TEXT_STYLE_ITALIC
};

/**
 * \brief Abstract Text class.
 *
 * Texts can render glyphs using a TTF or OTF font file, or can use a
 * texture font but that is not implemented yet.
 *
 * Texts must be assigned an AFont with SetFont before being able to work.
 *
 * \see AFont
 */
class ENGINE_CLASS AText : public RenderableObject
{
public:
    AText(GameEngine* engine);
    virtual ~AText();

    AFont* TextFont;

    /**
     * \brief Get the text stored in this AText instance.
     *
     * \return std::string - Text contents.
     */
    virtual std::string* GetText() = 0;

    /**
     * \brief Set the text contents stored in this AText instance.
     *
     * \param text - Text contents.
     */
    virtual void SetText(std::string text) = 0;

    /**
     * \brief Get the AFont applied to this text.
     *
     * \return AFont - Font instance used by this text.
     */
    virtual AFont* GetFont() = 0;

    /**
     * \brief Set the font used by this text.
     *
     * \param font - Font object to use.
     */
    virtual void SetFont(AFont* font) = 0;

    /**
     * \brief Get the character size to use when drawing the text.
     *
     * \return int - Size of the font in "points".
     */
    virtual int GetCharacterSize() = 0;

    /**
     * \brief Get the character size to use when drawing the text.
     *
     * \param size - Size to use.
     */
    virtual void SetCharacterSize(int size) = 0;

    /**
     * \brief Get the text style option to use when drawing the text.
     *
     * \return TextStyle - Style that is being used.
     */
    virtual TextStyle GetStyle() = 0;

    /**
     * \brief Set the text style to use when drawing the text.
     *
     * Defaults to Regular
     *
     * \param style - Style object to use.
     */
    virtual void SetStyle(TextStyle style = TEXT_STYLE_REGULAR) = 0;

    /**
     * \brief Get the color of the text.
     *
     * \return uint32_t - Color used in the format used by the renderer, SDL
     * for example is ARGB.
     */
    virtual uint32_t GetColor() = 0;

    /**
     * \brief Set the color to use when drawing the text.
     *
     * \param color - Color used in the format used by the renderer, SDL
     * for example is ARGB.
     */
    virtual void SetColor(uint32_t color) = 0;
};