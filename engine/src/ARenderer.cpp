#include "ARenderer.h"

#include "ResourceManager.h"
#include "Asset.h"
#include "FormatLoaders/FrameListLoader.h"

ARenderer::ARenderer()
{
    LogTrace("ARenderer::ARenderer");
}

ARenderer::~ARenderer()
{
    LogTrace("ARenderer::~ARenderer");
}

ArrayList<ATexture*>* ARenderer::CreateTextureList(const char* fileNames[], int length)
{
    ArrayList<ATexture*>* framesList = new ArrayList<ATexture*>();

    for (int i = 0; i < length; i++)
    {
        const char* fileName = fileNames[i];

        ATexture* tex = this->CreateTexture(fileName);

        if (tex != NULL)
        {
            framesList->Add(tex);
        }
    }

    return framesList;
}

ArrayList<ATexture*>* ARenderer::LoadFrames(const char* path)
{
    FrameListLoader loader = FrameListLoader(path, this);
    
    return loader.ExtractAsTextures();
}

ATexture* ARenderer::CreateTexture(const char* filepath)
{
    Asset* result = this->Resman->GetResource(filepath);
    
    return this->CreateTexture(result);
}

ATexture* ARenderer::CreateTexture(Asset* asset)
{
    assert(asset != NULL);
    
    return this->CreateTexture(asset->GetData(), (int)asset->size);
}