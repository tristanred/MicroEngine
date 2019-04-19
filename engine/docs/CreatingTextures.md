# Creating Textures

Creating textures is meant to be as easy as possible. There are only 1 main
way to create texture and it is to call the CreateTexture method from the
Engine and giving it a name. The name can be a path to load a texture from
a known location but it can also be a texture identifier so you don't need to
use the exact full path every time, more on that later.

## Form 1

Creating a texture is always done through the GameEngine and there are helper
methods in a GameModule but they only redirect to GameEngine.

The main API is GameEngine::CreateTexture(string name). The 'textureName'
parameter is the identifier used to load the texture image. It can be a file
path or a 'friendly' name given to the texture if it was loaded manually.

```
GameModule* gameModule = this;

// Giving a full path
ATexture* tex = gameModule->CreateTexture("assets/engine/Enabled.png");

// Giving a texture name
ATexture* tex2 = gameModule->CreateTexture("button_enabled");
```

The result will be NULL if the texture was not found.

The resulting texture will use the size of the image as its texture size.

## Form 2

You can also create a blank texture and give it contents later. This can be
used to create programmatic textures.

```
GameModule* gameModule = this;

// Giving a full path
ATexture* tex = gameModule->CreateTexture();
tex->SetSolidColor(FSize(75, 75), 0xFFAA0000);
```

ATexture::SetSolidColor is one of the methods that will generate content for
a texture. In order to set a texture to a solid color, it needs to be given
a size first. When calling SetSolidColor you need to provide both upfront. The
other method ATexture::FillColor will use the existing size and fill the pixels
with the provided color.

