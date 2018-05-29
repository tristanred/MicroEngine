#pragma once

#include "core.h"
#include "TextureRepository.h"

class ENGINE_CLASS SDLTextureRepository : public TextureRepository
{
public:
    explicit SDLTextureRepository(ARenderer* renderer);
    ~SDLTextureRepository() override;

    ATexture* LoadFromFile(const char* filepath) override;
    ATexture* GetBySolidColor(uint32_t color) override;

};