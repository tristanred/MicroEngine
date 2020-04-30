#include "Rendering/NullRenderer/NullRenderer.h"
#include "Rendering/NullRenderer/NullTexture.h"

NullRenderer::NullRenderer() : ARenderer() {}

NullRenderer::~NullRenderer() {}

bool NullRenderer::Initialize()
{
    return true;
}

bool NullRenderer::Initialize(IConfigProvider* config)
{
    return true;
}

bool NullRenderer::Initialize(RendererParameters* params)
{
    return true;
}

void NullRenderer::Shutdown() {}

void NullRenderer::Draw(RenderableObject* renderObject) {}

void NullRenderer::DrawTexture(ATexture* texture, float posX, float posY) {}

void NullRenderer::DrawTexture(ATexture* texture,
                               float posX,
                               float posY,
                               struct TextureDrawOptions* opts)
{
}

FSize NullRenderer::GetWindowSize()
{
    return FSize(100, 100);
}

ATexture* NullRenderer::CreateTexture()
{
    return new NullTexture(this);
}

ATexture* NullRenderer::CreateTexture(void* data, int length)
{
    return new NullTexture(this);
}

void NullRenderer::DeleteTexture(ATexture* texture) {}

void NullRenderer::BeginDraw() {}

void NullRenderer::EndDraw() {}

void NullRenderer::ScreenshotNextFrame() {}

void NullRenderer::SaveToFile(RenderableObject* object, const char* path) {}