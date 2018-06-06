#include "GameEngine.h"

#include "GameModule.h"
#include "TextureRepository.h"
#include "libtech/Geometry.h"
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

#include "libtech/mytime.h"

GameEngine::GameEngine()
{
    this->Modules = new std::list<GameModule*>();

    GameLog = new FileLogger();
    GameLog->Open("gamelog.txt");
    GameLog->LogMessage("Game Log Initialized");
    RegisterLogger(GameLog);
    LogTrace("GameEngine::GameEngine");

    Renderer = NULL;
    TextureRepo = NULL;
    Mouse = NULL;
    Keyboard = NULL;
    Platform = NULL;

    InitializationComplete = false;
    currentFrameTime = 0;
    previousFrameTime = 0;
    wantedFPS = 60;
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

    delete(Platform);
    delete(Mouse);
    delete(Keyboard);
    delete(TextureRepo);
    delete(Renderer);

    GameLog->Close();
}

void GameEngine::Initialize()
{
    LogTrace("GameEngine::Initialize");

    Renderer = AbstractFactory::CreateRenderer();
    ConfigFile defaults = ConfigFile("assets/engine/engine_config.xml");
    bool renderInitSuccess = Renderer->Initialize(&defaults);

    Platform = AbstractFactory::CreatePlatformHandler(Renderer);
    TextureRepo = AbstractFactory::CreateTextureRepository(this->Renderer);
    Mouse = AbstractFactory::CreateMouse();
    Keyboard = AbstractFactory::CreateKeyboard();

    if (Renderer == NULL ||
        Platform == NULL ||
        TextureRepo == NULL ||
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
}

void GameEngine::Play()
{
    LogTrace("GameEngine::Play");

    while (true)
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

        if(Keyboard->IsKeyClicked(Key::_Escape))
        {
            return;
        }

        currentFrameTime = get_a_ticks();
        if(TimeForNextFrame())
        {
            // Setup Frame data
            previousFrameTime = currentFrameTime;

            // Update engine and game modules
            this->Update();

            // Draw stuff
            Renderer->BeginDraw();

            this->DrawModules();

            Renderer->EndDraw();
        }

        Keyboard->UpdateKeyboardPastState();
        Mouse->UpdatePastMouseState();
    }
}

void GameEngine::PlayOne()
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

    currentFrameTime = get_a_ticks();
    if (TimeForNextFrame())
    {
        // Setup Frame data
        previousFrameTime = currentFrameTime;

        // Update engine and game modules
        this->Update();

        // Draw stuff
        Renderer->BeginDraw();

        this->DrawModules();

        Renderer->EndDraw();
    }

    Keyboard->UpdateKeyboardPastState();
    Mouse->UpdatePastMouseState();
}

void GameEngine::PlayOneUnlocked()
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

    currentFrameTime = get_a_ticks();
    previousFrameTime = currentFrameTime;

    // Update engine and game modules
    this->Update();

    // Draw stuff
    Renderer->BeginDraw();

    this->DrawModules();

    Renderer->EndDraw();

    Keyboard->UpdateKeyboardPastState();
    Mouse->UpdatePastMouseState();
}

long GameEngine::GetDeltaTime()
{
    return currentFrameTime - previousFrameTime;
}

ASprite* GameEngine::CreateSprite()
{
    LogTrace("GameEngine::CreateSprite");

    ASprite* sprt = AbstractFactory::CreateSprite(Renderer);

    return sprt;
}

AText* GameEngine::CreateText()
{
    LogTrace("GameEngine::CreateText");

    AText* text = AbstractFactory::CreateText(this->Renderer);

    return text;
}

AFont* GameEngine::CreateFont()
{
    LogTrace("GameEngine::CreateFont");

    AFont* font = AbstractFactory::CreateFont(this->Renderer);

    return font;
}

void GameEngine::Update()
{
    auto begin = this->Modules->begin();
    auto end = this->Modules->end();

    while (begin != end)
    {
        GameModule* mod = *begin;

        mod->Update();

        begin++;
    }
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
    test->SetColor(0xFFFF0000);

    return test;
}

bool GameEngine::TimeForNextFrame()
{
    return GetDeltaTime() > 1000 / wantedFPS;
}

void GameEngine::Shutdown()
{
    LogTrace("GameEngine::Shutdown");

    Renderer->Shutdown();
    Platform->Shutdown();
}
