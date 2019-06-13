#pragma once

class ATexture;
class GameEngine;

#include "core.h"
#include "RenderableObject.h"
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
 * \brief Abstract renderable object that has some playback mechanism.
 *
 * Sprites that have any kind of playback need to have their update methods
 * called.
*/
class ENGINE_CLASS ASprite : public RenderableObject
{
public:
    ASprite(GameEngine* engine);
    virtual ~ASprite() override;

    /**
     * \brief Add an animation on this Sprite that can be played.
     *
     * To play an animation after it has been added, we must call the Play
     * method using the animation's name.
     *
     * \param anim - The animation to add.
     */
    virtual void AddAnimation(SpriteAnimation* anim);

    /**
     * \brief Setup from a file, automatically creates a texture and
     * applies it to itself.
     *
     * This sets the sprite to a single texture.
     *
     * \param filepath - Path to load as a texture.
     */
    virtual void SetTexture(const char* filepath);

    /**
     * \brief Setup the sprite with a sequence of file to be played as the
     * default animation.
     *
     * \param filepath - Array of file paths to load as a texture.
     * \param amount - Length of the paths array.
     */
    virtual void SetTexture(const char* filepath[], int amount);

    /**
     * \brief Setup the sprite with a single texture.
     *
     * \param texture - Target texture.
     */
    virtual void SetTexture(ATexture* texture) override;

    /**
     * \brief Setup the sprite with a list of textures to be played as the
     * default animation.
     *
     * \param textureList - List of textures
     */
    virtual void SetTexture(ArrayList<ATexture*>* textureList);

    /**
     * \brief Setup the sprite with a list of animations. Each can be played
     * with its name.
     *
     * \param animList - List of animations
     */
    virtual void SetTexture(ArrayList<SpriteAnimation*>* animList);

    /**
     * \brief Get the currently applied texture. When playing an animation, this
     * will return the current texture of the current animation at the current
     * frame.
     *
     * \return ATexture - The current texture.
     */
    virtual ATexture* GetTexture() override;

    /**
     * \brief Update the sprite.
     *
     * \param deltaTime - Difference of time between this frame and the last.
     */
    void Update(unsigned int deltaTime);

    /**
     * \brief Play an animation on the sprite.
     *
     * \param animName - Name of the animation to play.
     * \param loop - Set to true if the animation loops back to the start.
     * \param fps - Frames per second speed of the animation.
     */
    void Play(const char* animName = NULL, bool loop = false, int fps = 60);

    /**
     * \brief Stop the animation playback. Stops at the current frame.
     *
     * \remark Will be upgraded with a parameter to reset to the first frame.
     */
    void Stop();

protected:
    // Playback settings
    int framesPerSecond;
    long previousFrameTime;

    /**
     * \brief Check if is time to switch to the next frame.
     */
    bool isTimeForNextFrame();
    bool isPlaying;
    bool looping;

    // Animation settings
    int currentAnimationIndex;
    ArrayList<SpriteAnimation*>* spriteAnimations;

    /**
     * \brief Advance to the next frame.
     */
    void AdvanceFrame();
};