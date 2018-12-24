#include "ARenderer.h"

#include "TextureRepository.h"
#include "FormatLoaders/FrameListLoader.h"

ARenderer::ARenderer()
{
    LogTrace("ARenderer::ARenderer");

    TextureRepo = new TextureRepository();
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
