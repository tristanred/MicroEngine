#pragma once

class GameEngine;
class ARenderable;
class ASprite;
class AText;
class AFont;
class ATexture;
class ARenderer;
class Viewport;

#include <list>

#include "core.h"

class ENGINE_CLASS GameModule
{
public:
    explicit GameModule(GameEngine* engine);
    virtual ~GameModule();

    std::list<ARenderable*>* Objects;

    // Get game services
    ARenderer* GetRenderer();
    GameEngine* GetEngine();

    // Create renderer-specific objects.
    ASprite* CreateSprite();
    AText* CreateText();
    AFont* CreateFont();

    ATexture* CreateTexture(); // Create empty texture
    ATexture* CreateTexture(const char* filePath); // Create texture from file

    virtual Viewport* CreateViewport();

    virtual void AttachRenderable(ARenderable* object);

    virtual void Enabled();
    virtual void Disabled();
    
    virtual void Update(unsigned int deltaTime);
    virtual void Draw(ARenderer* renderer);

protected:
    bool moduleEnabled;

private:
    GameEngine* Engine;

};