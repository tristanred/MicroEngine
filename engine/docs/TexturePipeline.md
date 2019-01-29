# Texture Loading Pipeline

Here are the steps that happens when we try to load a texture.

Typically we start from a GameModule subclass. The subclass calls the base 
method CreateTexture(textureName) to initiate the process.

MyGameModule.cpp
```
GameModule* gameModule = this;

ATexture* texture = gameModule->CreateTexture("assets/engine/Enabled.png");
```

The GameModule's CreateTexture method is only a wrapper around the Engine's
CreateTexture.

The Engine also just forwards the call to the Renderer, the only source of 
texture instances.

The Renderer takes the texture name parameter and looks in the ResourceManager
for a resource that was loaded with the required name. When looking for a 
resource, the resource manager looks in several locations. The first location
is the Resource Cache, this is a list of all resources that have been 
explicitely loaded or that have been loaded from another source at an earlier
time.

If it does not find it, the Resource Manager will looks through each of it's 
Resource Roots. They are folders that have been registered and that can be 
enumerated recursively for the needed file. 

Then if the file is still not found, it will look inside the loaded Package
Files. They are not implemented yet but they are big binary files full of
concatenated files. 

The object returned by the Resource Manager is of type Asset. The Asset class
contains the data of the resource, in this case some image that can be applied 
on a texture.

With an Asset object, the Renderer can call the specific CreateTexture method
that works with an Asset. All calls to create a texture needs to come from an 
Asset class but the helper methods currently only take in a filePath.

The Asset's data and size is used to call the implementation specific 
CreateTexture method located in the specific AGL class.