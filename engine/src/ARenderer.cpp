#include "ARenderer.h"

#include "TextureRepository.h"

ARenderer::ARenderer()
{
    LogTrace("ARenderer::ARenderer");

    TextureRepo = new TextureRepository();
}

ARenderer::~ARenderer()
{
    LogTrace("ARenderer::~ARenderer");
}
