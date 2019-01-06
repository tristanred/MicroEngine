# Sprite Animations

## Overview
Animating sprites has always been a difficult operation to simplify. The many formats of sprite images packing, playback of frames, different types of texturing options applied.

The API proposed by MicroEngine aims to provide a simple way of animating a sprite but also provide many more complicated and dynamic ways for more possibilities.

Sprites are usually operated in two ways. In one way a sprite is used to show a single image such as a background or a panel. Other times a sprite is expected to be animated with one or many frame-based animations. Both ways are easily supported using the same functions, if we set a single texture to the sprite it will be a static image. If we inject a list of frames the sprite will be able to be animated. You can call the animations method on a single-frame sprite with no problems. The sprite will start the playback of a single frame causing no divergence from the main code path.

## Texture Setting API
Creating a sprite is done by getting an ASprite instance, an instance can be ordered from a GameModule or the GameEngine. Eventually the calls end up in the renderer class to get a specific graphic-backend instance.

```
ASprite* sprt = gameModule->CreateSprite();
```

At this point we get our textures. We can get a single teture or many textures for an animation.

```
// Creating and setting a single texture to a Sprite :
ATexture* tex = this->CreateTexture("blue_circle.png");

sprt->SetTexture(tex);
```

Often we want to load a list of frames for an animation. There are many methods to allow loading a multitude of different formats. Some animations are packed in a TexturePacker file or some of them are images with each frame appended left to right with descriptor file.

### Texture Packer loading using the Renderer
Loading a texture packer involves asking the Renderer to load up the .xml file and load the frames from the packed spritesheet.

```
// Loading a TexturePacker file using the renderer
ArrayList<ATexture*>* frames = this->GetRenderer()->LoadFrames("assets/engine/clock/tp.xml");

sprt->SetTexture(frames);

sprt->Play();
```

### Loading from list of files
If you already have a list of file names you can ask the renderer to create and load each images and return a list of textures.

```
char* frame1 = "a.png";
char* frame2 = "b.png";
char* frame3 = "c.png";
char* frame4 = "d.png";

char** framesList = new char*[frame1, frame2, frame3, frame4];

ArrayList<ATexture*>* frames = this->GetRenderer()->CreateTextureList(framesList, 4);

sprt->SetTexture(frames);

sprt->Play();
```

### Loading from Single Spritesheet
Unfortunately sometimes you get a spritesheet that was not packed through a logical format like TexturePacker. There are utilities to load a single image spritesheet and split it into a list of individual textures.

```
ATexture* textureStrip = currentModule->CreateTexture("spritesheet.png");

ArrayList<ATexture*>* splitted = textureStrip->SplitTexture(24);

sprt->SetTexture(splitted);

sprt->Play();
```

## Animations API
You might want to have a sprite that is capable of playback using multiple animations. Such as Idle -> Walk -> Run -> Idle. With this system, the same sprite can start playback of multiple animations.

An ASprite keeps a list of animations, each animation has a list of frames. This system is used even when a single texture is set on the sprite. Even setting a single texture on the sprite will create a SpriteAnimation, add the frame into the animation and set the new animation as the current sprite's animation.

Using the same pipeline creates a much simpler mechanism and predicable code-path for the Sprite's code.

Currently, adding multiple animations on a Sprite must be done by creating instances of SpriteAnimation manually, then adding the instances on the Sprite.

SpriteAnimations are created from an array of textures using the Static methods of the SpriteAnimation class.

```
ArrayList<ATexture*>* splitted = textureStrip->SplitTexture(24);

SpriteAnimation* idleAnim = SpriteAnimation::FromTextures(splitted);
idleAnim->SetName("Idle");

sprt->AddAnimation(idleAnim);
```

Sometimes you may load a spritesheet that contains many animations, you could separate each of the Array's textures one by one or you can use a utility method from SpriteAnimation to use a pattern to create an animation from a sub-selection of the list's elements.

```
ArrayList<ATexture*>* splitted = textureStrip->SplitTexture(24);

SpriteAnimation* idleAnim = SpriteAnimation::FromTextures(splitted, "0..6");
idleAnim->SetName("Idle");

SpriteAnimation* moveAnim = SpriteAnimation::FromTextures(splitted, "6..12");
moveAnim->SetName("Move");

SpriteAnimation* hurtAnim = SpriteAnimation::FromTextures(splitted, "12..24");
hurtAnim->SetName("Hurt");

sprt->AddAnimation(idleAnim);
sprt->AddAnimation(moveAnim);
sprt->AddAnimation(hurtAnim);

this->DinoSprite->Play("Idle");
```

The string pattern above "0..6" indicates that the frames [0, 1, 2, 3, 4, 5] will be taken. This enables us to quickly create and assign 3 animations from a single texture image.