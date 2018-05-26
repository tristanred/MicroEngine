#pragma once

class GameModule;
class ASprite;
class ARenderer;


#include <list>

#include "core.h"

#include "renderer.h"

class ENGINE_CLASS GameEngine
{
public:
    std::list<GameModule*>* Modules;

    ARenderer* Renderer;

    GameEngine();
    ~GameEngine();

    void Start();

    void Play();
    void PlayOne();
    void PlayOneUnlocked();

    // TModule has to inherit from GameModule
    template <typename TModule>
    TModule* CreateModule();

    ASprite* CreateSprite();

private:
    void Update();
    void Draw();


};

template<typename TModule>
TModule* GameEngine::CreateModule()
{
    TModule* newModule = new TModule(this);
    this->Modules->push_back(newModule);

    return newModule;
}