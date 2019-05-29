#include "Cocoa/CocoaTexture.h"

CocoaTexture::CocoaTexture(ARenderer* renderer)
    : ATexture(renderer)
{

}

CocoaTexture::~CocoaTexture()
{

}

void CocoaTexture::SetSize(FSize size)
{

}

void CocoaTexture::SetSolidColor(FSize size, uint32_t color)
{

}

void CocoaTexture::LoadFromFile(const char* filepath)
{

}

void CocoaTexture::FillColor(uint32_t color)
{

}

void CocoaTexture::StrokeRect(FRectangle rect, uint32_t size, uint32_t color)
{

}

void CocoaTexture::FillRect(FRectangle rect, uint32_t color)
{

}

void CocoaTexture::DrawLine(FPosition pos1, FPosition pos2, uint32_t color, uint32_t size)
{

}

void CocoaTexture::FreeTextureMemory()
{

}

void CocoaTexture::ReloadTexture()
{

}

ATexture* CocoaTexture::GetSubTexture(int x, int y, int width, int height)
{
    return NULL;
}

void CocoaTexture::CopyFrom(ATexture* other, FPosition sourcePos, FSize sourceSize, FPosition destPos)
{

}

void RefreshSDLTexture()
{

}
