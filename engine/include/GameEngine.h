#pragma once

class ASprite;
class ATexture;
class FileLogger;
class TextureRepository;

class AMouse;
class AKeyboard;

#include <list>
#include <cstdint>
using namespace std;

#include "core.h"
#include "ARenderer.h"
#include "GameModule.h"

class ENGINE_CLASS GameEngine
{
public:
    std::list<GameModule*>* Modules;

    // Game Services
    ARenderer* Renderer;
    TextureRepository* TextureRepo;
    FileLogger* GameLog;

    int wantedFPS;
    long int previousFrameTime;
    long int currentFrameTime;

    // Input devices
    AMouse* mouse;
    AKeyboard* keyboard;

    GameEngine();
    ~GameEngine();

    void Initialize();
    void Shutdown();

    void Play();
    void PlayOne();
    void PlayOneUnlocked();

    // TModule has to inherit from GameModule
    template <typename TModule = GameModule>
    TModule* CreateModule();

    ASprite* CreateSprite();

    ATexture* GetDefaultTexture();

private:
    void Update();
    void DrawModules();


    bool TimeForNextFrame();
};

template<typename TModule>
TModule* GameEngine::CreateModule()
{
    TModule* newModule = new TModule(this);
    this->Modules->push_back(newModule);

    return newModule;
}

