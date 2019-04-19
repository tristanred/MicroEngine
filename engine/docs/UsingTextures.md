# Using Textures

Textures are mainly used to be applied to Sprites or Renderable objects.

# Setting a textures to a Renderable object

There is only one function to call to set a texture on an object :

```
ARenderable* object = someObject;

ATexture* tex = gameModule->CreateTexture("grass.png");

object->SetTexture(tex);
```

When calling SetTexture on an object, the size of the object is not modified
to match the size of the texture.

(TODO : Should it ? Maybe detect if an
explicit size was assigned, if not, adopt the size of the texture ?) (TODO :
also calling setSize on a renderable resizes the texture but it should let
the renderer draw to the target under a different destination size to avoid
rescaling the texture).

# Using textures outside a Renderable object

Sometimes, all you want is to draw a red square on the screen. It can be
bothersome to encapsulate a single object in a Sprite just to draw it on the
screen. For this, the engine has specific methods to draw textures by
themselves :

```
GameModule* module = someModule;

ARenderer* gameRenderer = module->GetRenderer();

ATexture* tex = gameModule->CreateTexture("grass.png");

void Draw()
{
    gameRenderer->DrawTexture(tex, 10, 10);
}
```

Since the texture object cannot be added in a hierarchy of objects we must call
the draw method from inside our available draw loop, usually in our implemented
game module. Textures don't carry a position so we must indicate the location of
the draw.

# Manipulating the texture

Texture objects can be modified in a variety of ways. We have already seen how
to set the texture to a solid color in the [Creating Textures] page. We can also
change the size of the texture by calling SetSize(newSize), this will rescale
the texture to be rendered at the new size.

We can get a copy of an area of the texture by using GetSubTexture, this will
create a new Texture instance with that subsection.