#pragma once

class GameModule;
class ASprite;

#include <list>

#include "core.h"

class ENGINE_CLASS GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    std::list<GameModule*>* Modules;

    // TModule has to inherit from GameModule
    template <typename TModule>
    TModule* CreateModule();

    ASprite* CreateSprite();
};

template<typename TModule>
TModule* GameEngine::CreateModule()
{
    TModule* newModule = new TModule();
    this->Modules->push_back(newModule);

    return newModule;
}