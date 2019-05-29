#pragma once

class ARenderer;
class CocoaRenderer;

#include <cstdint>

#include "core.h"
#include "ATexture.h"
#include "libtech/geometry.h"

class ENGINE_CLASS CocoaTexture : public ATexture
{
public:
    explicit CocoaTexture(ARenderer* renderer);
    //CocoaTexture(ARenderer* renderer, SDL_Surface* fromSurface);
    virtual ~CocoaTexture() override;

    void SetSize(FSize size) override;

    void SetSolidColor(FSize size, uint32_t color) override;
    void LoadFromFile(const char* filepath) override;

    void FillColor(uint32_t color) override;

    void StrokeRect(FRectangle rect, uint32_t size, uint32_t color) override;
    void FillRect(FRectangle rect, uint32_t color) override;
    void DrawLine(FPosition pos1, FPosition pos2, uint32_t color, uint32_t size) override;

    void FreeTextureMemory() override;
    void ReloadTexture() override;

    ATexture* GetSubTexture(int x, int y, int width, int height) override;

    void CopyFrom(ATexture* other, FPosition sourcePos, FSize sourceSize, FPosition destPos) override;


    void RefreshSDLTexture();

    ARenderer* Renderer;
};
