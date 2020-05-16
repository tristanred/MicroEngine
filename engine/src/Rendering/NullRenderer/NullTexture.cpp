#include "Rendering/NullRenderer/NullTexture.h"

NullTexture::NullTexture(ARenderer* renderer) : ATexture(renderer)
{
    this->BaseRenderer = renderer;
}

NullTexture::~NullTexture() {}

void NullTexture::SetSize(FSize size) {}

void NullTexture::SetSolidColor(FSize size, uint32_t color) {}

void NullTexture::LoadFromFile(const char* filepath) {}

void NullTexture::FillColor(uint32_t color) {}

void NullTexture::StrokeRect(FRectangle rect, uint32_t size, uint32_t color) {}

void NullTexture::FillRect(FRectangle rect, uint32_t color) {}

void NullTexture::DrawLine(FPosition pos1,
                           FPosition pos2,
                           uint32_t color,
                           uint32_t size)
{
}

void NullTexture::FreeTextureMemory() {}

void NullTexture::ReloadTexture() {}

ATexture* NullTexture::GetSubTexture(int x, int y, int width, int height)
{
    return new NullTexture(this->BaseRenderer);
}

void NullTexture::CopyFrom(ATexture* other,
                           FPosition sourcePos,
                           FSize sourceSize,
                           FPosition destPos)
{
}
