#pragma once

#include "core.h"
#include <string.h>
#include <string>

class ENGINE_CLASS AFont
{
public:
    AFont();
    virtual ~AFont();
    
    // Load a TTF file
    virtual void LoadFontFile(std::string path) = 0;
};