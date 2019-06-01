#pragma once

#if SUPPORT_COCOA == 1

class Asset;

#include "core.h"
#include "AFont.h"

class ENGINE_CLASS CocoaFont : public AFont
{
public:
    CocoaFont();
    virtual ~CocoaFont() override;

    void LoadFontFile(std::string path) override;

    void LoadFontFile(Asset* asset) override;
};

#endif