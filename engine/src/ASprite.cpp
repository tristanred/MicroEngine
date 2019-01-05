#include "ASprite.h"

#include "libtech/geometry.h"
#include "ARenderer.h"
#include "ATexture.h"
#include <libtech/mytime.h>

SpriteAnimation* SpriteAnimation::FromTextures(ArrayList<ATexture *>* list, const char* pattern)
{
    char* patternCopy = new char[strlen(pattern)+1];
    strcpy(patternCopy, pattern);

    int startFrame = -1;
    int endFrame = -1;

    char* token = strtok(patternCopy, "..");
    while(token)
    {
        if(startFrame == -1)
        {
            startFrame = atoi(token);
        }
        else
        {
            endFrame = atoi(token);
        }

        token = strtok(NULL, "..");
    }
    delete[] patternCopy;

    SpriteAnimation* newAnim = new SpriteAnimation();
    newAnim->AnimationName = NULL;
    newAnim->currentFrameIndex = 0;
    newAnim->Textures = new ArrayList<ATexture*>();

    for(int i = startFrame; i < endFrame; i++)
    {
        newAnim->Textures->Add(list->Get(i));
    }

    return newAnim;
}

SpriteAnimation* SpriteAnimation::FromTextures(ATexture* first, ...)
{
    SpriteAnimation* newAnim = new SpriteAnimation();
    newAnim->AnimationName = NULL;
    newAnim->currentFrameIndex = 0;
    newAnim->Textures = new ArrayList<ATexture*>();

    va_list args;
    va_start(args, first);

    ATexture* nextTexture = first;
    while(nextTexture != NULL)
    {
        newAnim->Textures->Add(nextTexture);

        nextTexture = va_arg(args, ATexture*);
    }
    va_end(args);

    return newAnim;
}

void SpriteAnimation::SetName(const char *name)
{
    if(this->AnimationName == NULL)
    {
        this->AnimationName = new char[256];
    }
    
    strcpy(this->AnimationName, name);
}


ASprite::ASprite(ARenderer *renderer) : ARenderable(renderer)
{
    LogTrace("ASprite::ASprite");

    this->position.X = 0;
    this->position.Y = 0;

    this->size.Width = 0;
    this->size.Height = 0;

    framesPerSecond = 0;
    previousFrameTime = 0;
    currentAnimationIndex = -1;
    spriteAnimations = NULL;

    isPlaying = false;
    looping = false;
}

ASprite::~ASprite()
{
    LogTrace("ASprite::~ASprite");
}

void ASprite::AddAnimation(SpriteAnimation *anim)
{
    // TODO
    if(spriteAnimations == NULL)
    {
        spriteAnimations = new ArrayList<SpriteAnimation*>();
        
        spriteAnimations->Add(anim);
        currentAnimationIndex = 0;
    }
    else
    {
        spriteAnimations->Add(anim);
    }
}

void ASprite::SetTexture(const char *filepath)
{
    if (filepath != NULL)
    {
        ATexture *tex = this->Renderer->CreateTexture(filepath);

        this->SetTexture(tex);
    }
}

void ASprite::SetTexture(ATexture *texture)
{
    if (texture != NULL)
    {
        ArrayList<ATexture *> *textureList = new ArrayList<ATexture *>();
        textureList->Add(texture);

        this->SetTexture(textureList);
    }
}

void ASprite::SetTexture(ArrayList<ATexture *> *textureList)
{
    if (textureList != NULL)
    {
        SpriteAnimation *anim = new SpriteAnimation();
        anim->currentFrameIndex = 0;
        anim->AnimationName = NULL;
        anim->Textures = textureList;

        ArrayList<SpriteAnimation *> *animList = new ArrayList<SpriteAnimation *>();
        animList->Add(anim);

        this->SetTexture(animList);
    }
}

void ASprite::SetTexture(ArrayList<SpriteAnimation *> *animList)
{
    if (animList != NULL)
    {
        currentAnimationIndex = 0;
        this->spriteAnimations = animList;
    }
}

void ASprite::SetTexture(const char *filepath[], int amount)
{
}

ATexture *ASprite::GetTexture()
{
    if (spriteAnimations != NULL && spriteAnimations->Count() > currentAnimationIndex)
    {
        int textureIndex = spriteAnimations->Get(currentAnimationIndex)->currentFrameIndex;
        ATexture *ct = spriteAnimations->Get(currentAnimationIndex)->Textures->Get(textureIndex);

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

void ASprite::Play(const char* animName, bool loop, int fps)
{
    // Find the animation with the correct name
    for(int i = 0; i < this->spriteAnimations->Count(); i++)
    {
        SpriteAnimation* anim = this->spriteAnimations->Get(i);
        
        if( (animName == NULL && anim->AnimationName == NULL) ||
           strcmp(anim->AnimationName, animName) == 0)
        {
            this->currentAnimationIndex = i;
            this->looping = loop;
            this->framesPerSecond = fps;
            
            this->isPlaying = true;
        }
    }
}

void ASprite::Stop()
{
    this->isPlaying = false;
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
    SpriteAnimation *currentAnim = this->spriteAnimations->Get(currentAnimationIndex);

    currentAnim->currentFrameIndex++;

    if (currentAnim->currentFrameIndex >= currentAnim->Textures->Count())
    {
        if (this->looping == true)
        {
            currentAnim->currentFrameIndex = 0;
        }
        else
        {
            currentAnim->currentFrameIndex = (int)currentAnim->Textures->Count() - 1;
        }
    }
}
