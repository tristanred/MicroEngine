#pragma once

class ASprite;
class ATexture;
class FileLogger;
class TextureRepository;
class FileCache;
class APlatform;
class AMouse;
class AKeyboard;
class Viewport;
class DebugLayer;
class ResourceManager;

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
    FileLogger* GameLog;
    FileCache* FilesCache;
    ResourceManager* ResManager;

    int wantedFPS;
    long int previousFrameTime;
    long int currentFrameTime;

    // Engine State
    bool InitializationComplete;

    // Input devices
    AMouse* Mouse;
    AKeyboard* Keyboard;

    // Platform manager
    APlatform* Platform;

    // Debugging
    DebugLayer* debugLayer;

    GameEngine();
    ~GameEngine();

    void Initialize();
    void Shutdown();

    void Play();
    void PlayOne();
    void PlayOneUnlocked();

    long GetDeltaTime();

    // TModule has to inherit from GameModule
    template <typename TModule = GameModule>
    TModule* CreateModule();

    ASprite* CreateSprite();
    AText * CreateText();
    AFont* CreateTextFont();
    ATexture * CreateTexture();
    ATexture * CreateTexture(const char* filepath);

    void ReleaseObject(ATexture* DebugDarkplate);
    void ReleaseObject(ARenderable* DebugDarkplate);

    ATexture* GetDefaultTexture();

    // -------------------- Viewport --------------------
    std::list<Viewport*>* GameViewports;

    void SelectViewport(Viewport* view);
    Viewport* CreateViewport();
    Viewport* GetCurrentViewport();

    void ShowDebugLayer();
    void HideDebugLayer();

private:
    void Update(unsigned int deltaTime);
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

