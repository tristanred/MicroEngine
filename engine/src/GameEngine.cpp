#include "GameEngine.h"

#include <libtech/filecache.h>
#include <libtech/mytime.h>
#include <libtech/sysutils.h>

#include <algorithm>

#include "Config/FileConfigProvider.h"
#include "Config/IConfigProvider.h"
#include "Debugging/DebugLayer.h"
#include "GameModule.h"
#include "Input/AKeyboard.h"
#include "Input/AMouse.h"
#include "Rendering/AFont.h"
#include "Rendering/APlatform.h"
#include "Rendering/ARenderer.h"
#include "Rendering/ASprite.h"
#include "Rendering/AText.h"
#include "Rendering/ATexture.h"
#include "Rendering/AbstractFactory.h"
#include "ResourceManager.h"
#include "Viewport.h"
#include "libtech/filelogger.h"
#include "libtech/geometry.h"


#ifdef __APPLE__
#include <time.h>
#endif

GameEngine::GameEngine()
{
    this->Modules = new std::list<GameModule*>();

    this->GameViewports = new std::list<Viewport*>();

    GameLog = new FileLogger();
    GameLog->Open("gamelog.txt");
    GameLog->LogMessage("Game Log Initialized");
    RegisterLogger(GameLog);
    LogTrace("GameEngine::GameEngine");

    Renderer = NULL;
    FilesCache = NULL;
    ResManager = NULL;
    Mouse = NULL;
    Keyboard = NULL;
    Platform = NULL;
    Config = NULL;

    InitializationComplete = false;
    currentFrameTime = 0;
    previousFrameTime = 0;
    wantedFPS = 60;

    this->debugLayer = NULL;
}

GameEngine::~GameEngine()
{
    LogTrace("GameEngine::~GameEngine");

    auto modbegin = Modules->begin();
    auto modend = Modules->end();
    while(modbegin != modend)
    {
        GameModule* mod = *modbegin;
        delete(mod);

        modbegin++;
    }
    Modules->clear();
    delete(Modules);

    delete(this->debugLayer);

    delete(FilesCache);
    delete(ResManager);

    delete(Platform);
    delete(Mouse);
    delete(Keyboard);
    delete(Renderer);
    delete(Config);

    GameLog->Close();
}

void GameEngine::Initialize(EngineInitParams* params)
{
    LogTrace("GameEngine::Initialize");
    char* cwd = get_working_directory();
    char msg[2048];
    sprintf(msg, "Working Directory is : %s", cwd);
    LogMessage(msg);

    FilesCache = new FileCache();
    ResManager = new ResourceManager();
    ResManager->AddAssetRoot("assets/engine");

    Renderer = AbstractFactory::CreateRenderer();
    Renderer->Cache =
        FilesCache;  // Give the renderer a handle to the global cache
    Renderer->Resman = ResManager;

    FileConfigProvider* engineConfig =
        new FileConfigProvider("assets/engine/engine_config.xml");

    if(params != NULL)
    {
        this->Config = params->gameLocalConfig;
        this->Config->AttachProvider(engineConfig);
    }
    else
    {
        this->Config = engineConfig;
    }

    bool renderInitSuccess = Renderer->Initialize(this->Config);

    Platform = AbstractFactory::CreatePlatformHandler(this);
    Mouse = AbstractFactory::CreateMouse();
    Keyboard = AbstractFactory::CreateKeyboard();

    this->Renderer->RenderViewport = this->CreateViewport();
    this->Renderer->RenderViewport->ViewRange =
        FRectangle(0, 0, Renderer->GetWindowSize().Width,
                   Renderer->GetWindowSize().Height);

    this->debugLayer = new DebugLayer(this);

    if(Renderer == NULL || Platform == NULL || Mouse == NULL ||
       Keyboard == NULL || renderInitSuccess == false)
    {
        LogError("Problem initializing one or many systems. Exiting...");

        InitializationComplete = false;

        return;
    }
    else
    {
        InitializationComplete = true;
    }

    currentFrameTime = get_a_ticks();
    previousFrameTime = get_a_ticks();
}

void GameEngine::Play()
{
    LogTrace("GameEngine::Play");

    while(true)
    {
        currentFrameTime = get_a_ticks();
        if(TimeForNextFrame())
        {
            Platform->HandleEvents();

            Keyboard->UpdateKeyboardState();
            Mouse->UpdateMouseState();

            if(Platform->RequestExit)
            {
                return;
            }

            if(Mouse->LeftButtonClicked())
            {
                printf("LEFT CLICKED\n");
            }

            if(Mouse->RightButtonPressed())
            {
                printf("Right Pressed\n");
            }

            if(Keyboard->IsKeyClicked(Key::_Escape))
            {
                return;
            }

            // Update engine and game modules
            this->Update(GetDeltaTime());

            // Draw stuff
            Renderer->BeginDraw();

            this->DrawModules();

            this->debugLayer->Draw(Renderer);

            Renderer->EndDraw();

            previousFrameTime = currentFrameTime;

            Keyboard->UpdateKeyboardPastState();
            Mouse->UpdatePastMouseState();
        }
        else
        {
#if __APPLE__
            /* macOS performance optimization.
             * This is mostly to save battery life and CPU cycles. Calling
             * get_a_ticks each frame ends up calling gettimeofday quite often
             * and this functions costs a lot. Instead of polling each loop
             * we just sleep for 1ms to be
             * sleeping for most of the time. The timer should be lowered to a
             * much smaller value when the weight of the engine becomes higher.
             * Even sleeping for 1ms is a major improvement.
             */

            struct timespec x;
            x.tv_nsec = 1000 * 1000 * 1;  // 1ms
            x.tv_sec = 0;
            nanosleep(&x, NULL);
#endif
        }
    }
}

void GameEngine::PlayOne()
{
    currentFrameTime = get_a_ticks();
    if(TimeForNextFrame())
    {
        Platform->HandleEvents();

        Keyboard->UpdateKeyboardState();
        Mouse->UpdateMouseState();

        if(Platform->RequestExit)
        {
            return;
        }

        if(Mouse->LeftButtonClicked())
        {
            printf("LEFT CLICKED\n");
        }

        if(Mouse->RightButtonPressed())
        {
            printf("Right Pressed\n");
        }

        if(Keyboard->IsKeyClicked(Key::_Escape))
        {
            return;
        }

        // Update engine and game modules
        this->Update(GetDeltaTime());

        // Draw stuff
        Renderer->BeginDraw();

        this->DrawModules();

        this->debugLayer->Draw(Renderer);

        Renderer->EndDraw();

        previousFrameTime = currentFrameTime;

        Keyboard->UpdateKeyboardPastState();
        Mouse->UpdatePastMouseState();
    }
}

void GameEngine::PlayOneUnlocked()
{
    currentFrameTime = get_a_ticks();

    Platform->HandleEvents();

    Keyboard->UpdateKeyboardState();
    Mouse->UpdateMouseState();

    if(Platform->RequestExit)
    {
        return;
    }

    if(Mouse->LeftButtonClicked())
    {
        printf("LEFT CLICKED\n");
    }

    if(Mouse->RightButtonPressed())
    {
        printf("Right Pressed\n");
    }

    if(Keyboard->IsKeyClicked(Key::_Escape))
    {
        return;
    }

    // Update engine and game modules
    this->Update(GetDeltaTime());

    // Draw stuff
    Renderer->BeginDraw();

    this->DrawModules();

    this->debugLayer->Draw(Renderer);

    Renderer->EndDraw();

    previousFrameTime = currentFrameTime;

    Keyboard->UpdateKeyboardPastState();
    Mouse->UpdatePastMouseState();
}

long GameEngine::GetDeltaTime()
{
    return currentFrameTime - previousFrameTime;
}

GameModule* GameEngine::LoadModule(GameModule* targetModule)
{
    auto value =
        std::find(this->Modules->begin(), this->Modules->end(), targetModule);

    if(value == this->Modules->end())
    {
        // This module was not added in the stack. It was not created
        // correctly by calling CreateModule first.
        LogError("TODO ERROR");

        return NULL;
    }

    if(targetModule->ModuleState != GameModuleState::UNINITIALIZED)
    {
        LogError("Called Load on an Module on state %i",
                 targetModule->ModuleState);

        return NULL;
    }

    targetModule->Load();

    return targetModule;
}

GameModule* GameEngine::ActivateModule(GameModule* targetModule)
{
    auto value =
        std::find(this->Modules->begin(), this->Modules->end(), targetModule);

    if(value == this->Modules->end())
    {
        // This module was not added in the stack. It was not created
        // correctly by calling CreateModule first.
        LogError("TODO ERROR");

        return NULL;
    }

    if(targetModule->ModuleState != GameModuleState::LOADED)
    {
        LogError("Called Activate on an Module on state %i",
                 targetModule->ModuleState);

        return NULL;
    }

    targetModule->Activate();

    return targetModule;
}

void GameEngine::CloseModule(GameModule* targetModule)
{
    auto value =
        std::find(this->Modules->begin(), this->Modules->end(), targetModule);

    if(value == this->Modules->end())
    {
        // This module was not added in the stack. It was not created
        // correctly by calling CreateModule first.
        LogError("TODO ERROR");
    }

    if(targetModule->ModuleState == GameModuleState::ACTIVATED)
    {
        targetModule->Stop();
    }
    if(targetModule->ModuleState == GameModuleState::LOADED)
    {
        targetModule->Unload();
    }

    this->Modules->remove(targetModule);
    delete(targetModule);
}

// ASprite* GameEngine::CreateSprite()
// {
//     LogTrace("GameEngine::CreateSprite");

//     ASprite* sprt = AbstractFactory::CreateSprite(Renderer);

//     return sprt;
// }

AText* GameEngine::CreateText()
{
    LogTrace("GameEngine::CreateText");

    AText* text = AbstractFactory::CreateText(this);

    return text;
}

AFont* GameEngine::CreateTextFont()
{
    LogTrace("GameEngine::CreateTextFont");

    AFont* font = AbstractFactory::CreateTextFont(this);

    return font;
}

ATexture* GameEngine::CreateTexture()
{
    LogTrace("GameEngine::CreateTexture");

    ATexture* newTexture = AbstractFactory::CreateTexture(this);

    return newTexture;
}

ATexture* GameEngine::CreateTexture(const char* textureName)
{
    LogTrace("GameEngine::CreateTexture(char*)");

    ATexture* tex = this->Renderer->CreateTexture(textureName);

    return tex;
}

void GameEngine::Update(unsigned int deltaTime)
{
    if(Keyboard->IsKeyPressed(F1))
    {
        if(this->debugLayer->IsOpen())
        {
            this->debugLayer->Hide();
        }
        else
        {
            this->debugLayer->Show();
        }
    }

    // Update the viewports first
    auto vpBegin = this->GameViewports->begin();
    auto vpEnd = this->GameViewports->end();
    while(vpBegin != vpEnd)
    {
        Viewport* mod = *vpBegin;

        mod->Update();

        vpBegin++;
    }

    // Then update the sprites(renderables)
    auto begin = this->Modules->begin();
    auto end = this->Modules->end();
    while(begin != end)
    {
        GameModule* mod = *begin;

        // Modules must be at least loaded to receive an update
        if(mod->ModuleState >= GameModuleState::LOADED)
        {
            mod->Update(deltaTime);
        }

        begin++;
    }

    this->debugLayer->Update(deltaTime);
}

void GameEngine::DrawModules()
{
    auto begin = this->Modules->begin();
    auto end = this->Modules->end();

    while(begin != end)
    {
        GameModule* mod = *begin;

        // Modules receive a draw if they are activated
        if(mod->ModuleState == GameModuleState::ACTIVATED)
        {
            mod->Draw(Renderer);
        }

        begin++;
    }
}

ATexture* GameEngine::GetDefaultTexture()
{
    ATexture* test = AbstractFactory::CreateTexture(this);

    test->SetSize(FSize(100, 100));
    test->FillColor(0xFFFF0000);

    return test;
}

bool GameEngine::TimeForNextFrame()
{
    return GetDeltaTime() > 1000 / wantedFPS;
}

Viewport* GameEngine::GetCurrentViewport()
{
    return this->Renderer->RenderViewport;
}

FPosition GameEngine::GetMouseRelativePosition()
{
    FPosition pos;

    vec2 currentMousePos = this->Mouse->GetMousePosition();
    Viewport* currentVp = this->Renderer->RenderViewport;

    pos.X = currentMousePos.x + currentVp->CurrentView.X;
    pos.Y = currentMousePos.y + currentVp->CurrentView.Y;

    return pos;
}

void GameEngine::ReleaseObject(RenderableObject* renderableObject)
{
    // Temporary implementation. Instead of deleting the object, just de-parent
    // it and set it invisible.
    // This is because there is a lot of work still to be done for dynamic
    // object deallocation.

    renderableObject->Show(false);

    auto parent = renderableObject->GetParent();
    if(parent != NULL)
    {
        parent->RemoveChild(renderableObject);
    }

    delete(renderableObject);
}

void GameEngine::ReleaseObject(ATexture* textureObject)
{
    this->Renderer->DeleteTexture(textureObject);
}

void GameEngine::SelectViewport(Viewport* view)
{
    this->Renderer->RenderViewport = view;
}

Viewport* GameEngine::CreateViewport()
{
    Viewport* newVp = new Viewport();
    newVp->CurrentView = FRectangle(0, 0, this->Renderer->GetWindowSize().Width,
                                    this->Renderer->GetWindowSize().Height);

    if(this->Renderer->RenderViewport == NULL)
    {
        this->Renderer->RenderViewport = newVp;
    }

    this->GameViewports->push_back(newVp);

    return newVp;
}

void GameEngine::ShowDebugLayer()
{
    this->debugLayer->Show();
}

void GameEngine::HideDebugLayer()
{
    this->debugLayer->Hide();
}

void GameEngine::Shutdown()
{
    LogTrace("GameEngine::Shutdown");

    Renderer->Shutdown();
    Platform->Shutdown();
}
