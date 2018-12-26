#pragma once

class Asset;

#include "core.h"
#include <string.h>
#include <string>

/**
 * Abstract font class. Fonts contain the glyph information needed by a Text
 * to draw characters. Fonts can be provided in two formats : from a font file
 * like ttf or otf. Or from a spritesheet font, not supported yet.
 */
class ENGINE_CLASS AFont
{
public:
    AFont();
    virtual ~AFont();
    
    // Load a TTF file
    virtual void LoadFontFile(std::string path) = 0;
    
    virtual void LoadFontFile(Asset* asset) = 0;
};