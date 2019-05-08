#include "GameEngine.h"

#include "GameModule.h"
#include "libtech/geometry.h"
#include "libtech/filelogger.h"
#include "ConfigFile.h"
#include "AbstractFactory.h"
#include "ARenderer.h"
#include "APlatform.h"
#include "ASprite.h"
#include "AText.h"
#include "AFont.h"
#include "ATexture.h"
#include "Input/AMouse.h"
#include "Input/AKeyboard.h"
#include "Viewport.h"
#include "Debugging/DebugLayer.h"
#include "ResourceManager.h"

#include <libtech/filecache.h>
#include <libtech/sysutils.h>
#include <libtech/mytime.h>

#ifdef __APPLE__
#include <time.h>
#endif

GameEngine::GameEngine()
{
    this->Modules = new std::list<GameModule*>();

    this->GameViewports = new std::list<Viewport *>();

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
    while (modbegin != modend)
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

    GameLog->Close();
}

void GameEngine::Initialize()
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
    Renderer->Cache = FilesCache; // Give the renderer a handle to the global cache
    Renderer->Resman = ResManager;

    this->Renderer->RenderViewport = this->CreateViewport();
    this->Renderer->RenderViewport->ViewRange = FRectangle(0, 0, Renderer->GetWindowSize().Width, Renderer->GetWindowSize().Height);

    ConfigFile defaults = ConfigFile("assets/engine/engine_config.xml");
    bool renderInitSuccess = Renderer->Initialize(&defaults);

    Platform = AbstractFactory::CreatePlatformHandler(Renderer);
    Mouse = AbstractFactory::CreateMouse();
    Keyboard = AbstractFactory::CreateKeyboard();

    this->debugLayer = new DebugLayer(this);

    if (Renderer == NULL ||
        Platform == NULL ||
        Mouse == NULL ||
        Keyboard == NULL ||
        renderInitSuccess == false)
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

    while (true)
    {
        currentFrameTime = get_a_ticks();
        if(TimeForNextFrame())
        {
            Platform->HandleEvents();

            Keyboard->UpdateKeyboardState();
            Mouse->UpdateMouseState();

            if (Platform->RequestExit)
            {
                return;
            }

            if (Mouse->LeftButtonClicked())
            {
                printf("LEFT CLICKED\n");
            }

            if (Mouse->RightButtonPressed())
            {
                printf("Right Pressed\n");
            }

            if (Keyboard->IsKeyClicked(Key::_Escape))
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
             * we just sleep for 16ms to be able to hit 60fps max and be sleeping
             * for most of the time. The timer should be lowered to a much smaller
             * value when the weight of the engine becomes higher. Even sleeping
             * for 1ms is a major improvement.
             */

            struct timespec x;
            x.tv_nsec = 1000 * 1000 * 1; // 16ms
            x.tv_sec = 0;
            nanosleep(&x, NULL);
#endif
        }
    }
}

void GameEngine::PlayOne()
{
    currentFrameTime = get_a_ticks();
    if (TimeForNextFrame())
    {
        Platform->HandleEvents();

        Keyboard->UpdateKeyboardState();
        Mouse->UpdateMouseState();

        if (Platform->RequestExit)
        {
            return;
        }

        if (Mouse->LeftButtonClicked())
        {
            printf("LEFT CLICKED\n");
        }

        if (Mouse->RightButtonPressed())
        {
            printf("Right Pressed\n");
        }

        if (Keyboard->IsKeyClicked(Key::_Escape))
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

    if (Platform->RequestExit)
    {
        return;
    }

    if (Mouse->LeftButtonClicked())
    {
        printf("LEFT CLICKED\n");
    }

    if (Mouse->RightButtonPressed())
    {
        printf("Right Pressed\n");
    }

    if (Keyboard->IsKeyClicked(Key::_Escape))
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

// ASprite* GameEngine::CreateSprite()
// {
//     LogTrace("GameEngine::CreateSprite");

//     ASprite* sprt = AbstractFactory::CreateSprite(Renderer);

//     return sprt;
// }

AText* GameEngine::CreateText()
{
    LogTrace("GameEngine::CreateText");

    AText* text = AbstractFactory::CreateText(this->Renderer);

    return text;
}

AFont* GameEngine::CreateTextFont()
{
    LogTrace("GameEngine::CreateTextFont");

    AFont* font = AbstractFactory::CreateTextFont(this->Renderer);

    return font;
}

ATexture* GameEngine::CreateTexture()
{
    LogTrace("GameEngine::CreateTexture");

    ATexture* newTexture = AbstractFactory::CreateTexture(Renderer);

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
    if (Keyboard->IsKeyPressed(F1))
    {
        if (this->debugLayer->IsOpen())
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
    while (vpBegin != vpEnd)
    {
        Viewport* mod = *vpBegin;

        mod->Update();

        vpBegin++;
    }

    // Then update the sprites(renderables)
    auto begin = this->Modules->begin();
    auto end = this->Modules->end();
    while (begin != end)
    {
        GameModule* mod = *begin;

        mod->Update(deltaTime);

        begin++;
    }

    this->debugLayer->Update(deltaTime);
}

void GameEngine::DrawModules()
{
    auto begin = this->Modules->begin();
    auto end = this->Modules->end();

    while (begin != end)
    {
        GameModule* mod = *begin;

        mod->Draw(Renderer);

        begin++;
    }
}

ATexture* GameEngine::GetDefaultTexture()
{
    ATexture* test = AbstractFactory::CreateTexture(this->Renderer);

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

void GameEngine::ReleaseObject(ARenderable* textureObject)
{
}

void GameEngine::ReleaseObject(ATexture* renderableObject)
{
}

void GameEngine::SelectViewport(Viewport* view)
{
    this->Renderer->RenderViewport = view;
}

Viewport* GameEngine::CreateViewport()
{
    Viewport* newVp = new Viewport();
    newVp->CurrentView = FRectangle(0, 0, this->Renderer->GetWindowSize().Width, this->Renderer->GetWindowSize().Height);

    if (this->Renderer->RenderViewport == NULL)
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
