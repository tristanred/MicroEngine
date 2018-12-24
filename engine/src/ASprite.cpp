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
    currentAnimationIndex = false;
    spriteAnimations = NULL;
    
    isPlaying = false;
    looping = false;
}

ASprite::~ASprite()
{
    LogTrace("ASprite::~ASprite");
}

void ASprite::SetTexture(const char* filepath)
{
    if (filepath != NULL)
    {
        ATexture* tex = this->Renderer->CreateTexture(filepath);

        this->SetTexture(tex);
    }
}

void ASprite::SetTexture(ATexture* texture)
{
    if (texture != NULL)
    {
        ArrayList<ATexture*>* textureList = new ArrayList<ATexture*>();
        textureList->Add(texture);

        this->SetTexture(textureList);
    }
}

void ASprite::SetTexture(ArrayList<ATexture*>* textureList)
{
    if (textureList != NULL)
    {
        SpriteAnimation* anim = new SpriteAnimation();
        anim->currentFrameIndex = 0;
        anim->AnimationName = NULL;
        anim->Textures = textureList;

        ArrayList<SpriteAnimation*>* animList = new ArrayList<SpriteAnimation*>();
        animList->Add(anim);

        this->SetTexture(animList);
    }
}

void ASprite::SetTexture(ArrayList<SpriteAnimation*>* animList)
{
    if (animList != NULL)
    {
        currentAnimationIndex = 0;
        this->spriteAnimations = animList;
    }
}

ATexture* ASprite::GetTexture()
{
    if (spriteAnimations != NULL && spriteAnimations->Count() > currentAnimationIndex)
    {
        int textureIndex = spriteAnimations->Get(currentAnimationIndex)->currentFrameIndex;
        ATexture* ct = spriteAnimations->Get(currentAnimationIndex)->Textures->Get(textureIndex);

        assert(ct != NULL);

        return ct;
    }
    
    return NULL;
}

void ASprite::Update(unsigned int deltaTime)
{
    (void)deltaTime; // Unused for now

    if (this->isPlaying == true && isTimeForNextFrame())
    {
        this->previousFrameTime = get_a_ticks();
        
        this->AdvanceFrame();
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

void ASprite::AdvanceFrame()
{
    SpriteAnimation* currentAnim = this->spriteAnimations->Get(currentAnimationIndex);
    
    currentAnim->currentFrameIndex++;
    
    if(currentAnim->currentFrameIndex >= currentAnim->Textures->Count())
    {
        if(this->looping == true)
        {
            currentAnim->currentFrameIndex = 0;
        }
        else
        {
            currentAnim->currentFrameIndex = currentAnim->Textures->Count() - 1;
        }
    }
}

