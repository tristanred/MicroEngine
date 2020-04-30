#pragma once

class Asset;

#include "Rendering/AFont.h"
#include "core.h"

#define DefaultLoadedFontSize 22

class ENGINE_CLASS NullFont : public AFont
{
public:
    NullFont();
    ~NullFont() override;

    void LoadFontFile(std::string path) override;

    void LoadFontFile(Asset* asset) override;
};
