#pragma once

class ATexture;

#include "core.h"
#include "ARenderable.h"
#include <libtech/arraylist.h>

/**
 * \brief Container class for a sprite's animation.
 *
 * An ASprite can have multiple instances of SpriteAnimation, one for each
 * animation of the sprite.
 */
class ENGINE_CLASS SpriteAnimation
{
public:
    char* AnimationName;
    int currentFrameIndex;
    ArrayList<ATexture*>* Textures;

    /**
     * \brief Set the name of this animation.
     *
     * A sprite uses the name of its animations to play them.
     *
     * \param name - Name of the animation
     */
    void SetName(const char* name);

    /**
     * \brief Create a SpriteAnimation from a list of textures.
     *
     * This method takes all the textures in the list to make the animation.
     *
     * \param list - List of textures
     * \return SpriteAnimation
     */
    static SpriteAnimation* FromTextures(ArrayList<ATexture*>* list);

    /**
     * \brief Create a SpriteAnimation from a list of textures and a pattern
     * to choose which frame from that list.
     *
     * This method is given a wide list of textures and the pattern is used to
     * pick frames from the list. The pattern's format is like this 0..4 to
     * choose the first 5 frames (because the last number is inclusive).
     *
     *
     * \param list - List of textures
     * \param pattern - String pattern to choose frames with.
     * \return SpriteAnimation
     */
    static SpriteAnimation* FromTextures(ArrayList<ATexture*>* list, const char* pattern);

    /**
     * \brief Create a SpriteAnimation from a variadic list of textures.
     *
     * The variadic argument is each texture that is going to make up the
     * animation.
     */
    static SpriteAnimation* FromTextures(ATexture*, ...); // Variadic of ATextures*
};

/*
 * \brief A Sprite is a renderable object that has some playback mechanism.
 *
 *
 *
*/
class ENGINE_CLASS ASprite : public ARenderable
{
public:
    ASprite(ARenderer* renderer);
    virtual ~ASprite() override;

    virtual void AddAnimation(SpriteAnimation* anim);

    /**
     * Setup from a file, automatically creates a textureand applies it to itself.
     */
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

    void Play(const char* animName = NULL, bool loop = false, int fps = 60);
    void Stop();

protected:
    // Playback settings
    int framesPerSecond;
    long previousFrameTime;
    bool isTimeForNextFrame();
    bool isPlaying;
    bool looping;

    // Animation settings
    int currentAnimationIndex;
    ArrayList<SpriteAnimation*>* spriteAnimations;

    void AdvanceFrame();

};


