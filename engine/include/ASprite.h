#pragma once

class ATexture;

#include "core.h"
#include "ARenderable.h"
#include <libtech/arraylist.h>

struct ENGINE_CLASS SpriteAnimation
{
    char* AnimationName;
    int currentFrameIndex;
    ArrayList<ATexture*>* Textures;
};

/*
 * A Sprite is a renderable object that has some playback mechanism
 *
 *
 *
*/
class ENGINE_CLASS ASprite : public ARenderable
{
public:
    ASprite(ARenderer* renderer);
    virtual ~ASprite() override;

    // Setup from a file, automatically creates a textureand applies it to itself.
    virtual void SetTexture(const char* filepath);

    virtual void SetTexture(const char* filepath[], int amount);

    // Set sprite with just a static image
    virtual void SetTexture(ATexture* texture) override;

    // Setup from a list of textures and use that as the only animation
    virtual void SetTexture(ArrayList<ATexture*>* textureList);

    // Setup from a list of animations
    virtual void SetTexture(ArrayList<SpriteAnimation*>* animList);

    virtual ATexture* GetTexture() override;

    void Update(unsigned int deltaTime);

    void Play(int fps, bool loop, char* animName = NULL);
    void Stop();

protected:
    // Playback settings
    int framesPerSecond;
    uint32_t previousFrameTime;
    bool isTimeForNextFrame();
    bool isPlaying;
    bool looping;

    // Animation settings
    int currentAnimationIndex;
    ArrayList<SpriteAnimation*>* spriteAnimations;

    void AdvanceFrame();

};


