#pragma once

class Asset;

#include "core.h"
#include <string.h>
#include <string>

/**
 *\brief Abstract font class.
 *
 * Fonts contain the glyph information needed by an AText to draw characters.
 * Fonts can be provided in two formats : from a font file like ttf or otf.
 * Or from a spritesheet font, not supported yet.
 *
 * \see AText
 */
class ENGINE_CLASS AFont
{
public:
    AFont();
    virtual ~AFont();

    /**
     * \brief Load a font file. File should be in TTF or OTF format.
     */
    virtual void LoadFontFile(std::string path) = 0;

    /**
     * \brief Load a font from an Asset instance.
     */
    virtual void LoadFontFile(Asset* asset) = 0;
};