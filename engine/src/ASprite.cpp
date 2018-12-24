#include "ASprite.h"

#include "libtech/geometry.h"
#include "ARenderer.h"
#include <libtech/mytime.h>

ASprite::ASprite(ARenderer* renderer) : ARenderable(renderer)
{
    LogTrace("ASprite::ASprite");

    this->position.X = 0;
    this->position.Y = 0;

    this->size.Width = 0;
    this->size.Height = 0;

    framesPerSecond = 0;
    previousFrameTime = 0;
    spriteAnimations = NULL;
}

ASprite::~ASprite()
{
    LogTrace("ASprite::~ASprite");
}

void ASprite::Setup(const char* filepath)
{
    if (filepath != NULL)
    {
        ATexture* tex = this->Renderer->CreateTexture(filepath);

        this->Setup(tex);
    }
}

void ASprite::Setup(ATexture* texture)
{
    if (texture != NULL)
    {
        ArrayList<ATexture*>* textureList = new ArrayList<ATexture*>();
        textureList->Add(texture);

        this->Setup(textureList);
    }
}

void ASprite::Setup(ArrayList<ATexture*>* textureList)
{
    if (textureList != NULL)
    {
        SpriteAnimation* anim = new SpriteAnimation();
        anim->currentFrameIndex = 0;
        anim->AnimationName = NULL;
        anim->Textures = textureList;

        ArrayList<SpriteAnimation*>* animList = new ArrayList<SpriteAnimation*>();
        animList->Add(anim);

        this->Setup(animList);
    }
}

void ASprite::Setup(ArrayList<SpriteAnimation*>* animList)
{
    if (animList != NULL)
    {
        currentAnimationIndex = 0;
        this->spriteAnimations = animList;
    }
}

//ATexture* ASprite::GetTexture()
//{
//    if (spriteAnimations != NULL && spriteAnimations->Count() > currentAnimationIndex)
//    {
//        int textureIndex = spriteAnimations->Get(currentAnimationIndex)->currentFrameIndex;
//        ATexture* ct = spriteAnimations->Get(currentAnimationIndex)->Textures->Get(textureIndex);
//
//        assert(ct != NULL);
//
//        return ct;
//    }
//}
//
//void ASprite::SetTexture(ATexture* texture)
//{
//    // Not sure what to do in this situation
//}

void ASprite::Update(unsigned int deltaTime)
{
    (void)deltaTime; // Unused for now

    if (isTimeForNextFrame())
    {
        this->previousFrameTime = get_a_ticks();
    }
}

bool ASprite::isTimeForNextFrame()
{
    long currentTime = get_a_ticks();

    long timeDiff = currentTime - previousFrameTime;
    if (timeDiff >= (1000 / framesPerSecond))
    {
        return true;
    }
    else
    {
        return false;
    }
}
