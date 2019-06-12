#include "ARenderer.h"

#include "ResourceManager.h"
#include "Asset.h"
#include "FormatLoaders/FrameListLoader.h"
#include "ASprite.h"
#include "ATexture.h"

ARenderer::ARenderer()
{
    LogTrace("ARenderer::ARenderer");

    this->Cache = NULL;
    this->Resman = NULL;
    this->RenderViewport = NULL;
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

ATexture* ARenderer::CreateTexture(const char* textureName)
{
    Asset* result = this->Resman->GetResource(textureName);

    if(result == NULL)
    {
        // No assets found
        printf("Creating texture [%s] failed.\n", textureName);

        return NULL;
    }

    return this->CreateTexture(result);
}

ATexture* ARenderer::CreateTexture(Asset* asset)
{
    assert(asset != NULL);

    return this->CreateTexture(asset->GetData(), (int)asset->size);
}

ATexture* ARenderer::MakeTextureFromAnimation(SpriteAnimation* anim)
{
    /* Lays out all frames of a SpriteAnim into a texture strip. For now
     * we just put everything on a single row. So check each anim frames for
     * the highest one and add each frame's width to get the total width.
     */


    float minWidth = 0;
    float minHeight = 0;

    for(int i = 0; i < anim->Textures->Count(); i++)
    {
        ATexture* texture = anim->Textures->Get(i);
        minWidth += texture->GetSize().Width;

        if(minHeight < texture->GetSize().Height)
        {
            minHeight = texture->GetSize().Height;
        }
    }

    ATexture* tex = this->CreateTexture();
    tex->SetSize(FSize(minWidth, minHeight));

    int currentWidth = 0;
    for(int i = 0; i < anim->Textures->Count(); i++)
    {
        ATexture* texture = anim->Textures->Get(i);
        //tex->CopyFrom(texture, FPosition(currentWidth, 0));
    }


    return tex;
}