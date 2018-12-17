#pragma once

class GameEngine;
class ARenderable;
class ASprite;
class AText;
class AFont;
class ATexture;
class ARenderer;
class Viewport;

class TickTimer;

#include <list>
#include <stdint.h>

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
    AFont* CreateTextFont();

    ATexture* CreateTexture(); // Create empty texture
    ATexture* CreateTexture(const char* filePath); // Create texture from file

    virtual Viewport* CreateViewport();

    virtual void AttachRenderable(ARenderable* object);

    virtual void Enabled();
    virtual void Disabled();

    virtual void Update(unsigned int deltaTime);
    virtual void Draw(ARenderer* renderer);

    // Helper objects management
    std::list<TickTimer*>* Timers;

    virtual TickTimer* CreateTimer(uint32_t totalTime);
    virtual void DestroyTimer(TickTimer* timer);


protected:
    bool moduleEnabled;

private:
    GameEngine* Engine;

    void UpdateTimers(uint32_t deltaTime);
};