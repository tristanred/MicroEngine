#include "GameEngine.h"

#include "ARenderer.h"
#include "GameModule.h"
#include "libtech/filelogger.h"
#include "TextureRepository.h"
#include "AbstractFactory.h"
#include "libtech/Geometry.h"
#include "ATexture.h"
#include "ConfigFile.h"
#include "Input/AMouse.h"
#include "Input/AKeyboard.h"

#include "libtech/mytime.h"

// Temp include of SDL for event handling
#include <SDL.h>

GameEngine::GameEngine()
{
    this->Modules = new std::list<GameModule*>();

    GameLog = new FileLogger();
    GameLog->Open("gamelog.txt");
    GameLog->LogMessage("Game Log Initialized");
    RegisterLogger(GameLog);
    LogTrace("GameEngine::GameEngine");

    currentFrameTime = 0;
    previousFrameTime = 0;
    wantedFPS = 60;
}

GameEngine::~GameEngine()
{
    LogTrace("GameEngine::~GameEngine");

    GameLog->Close();
}

void GameEngine::Initialize()
{
    LogTrace("GameEngine::Initialize");

    Renderer = AbstractFactory::CreateRenderer();

    ConfigFile defaults = ConfigFile("assets/engine/engine_config.xml");
    Renderer->Initialize(&defaults);

    TextureRepo = AbstractFactory::CreateTextureRepository(this->Renderer);

    mouse = AbstractFactory::CreateMouse();
    keyboard = AbstractFactory::CreateKeyboard();
}

void GameEngine::Play()
{
    LogTrace("GameEngine::Play");

    while (true)
    {
        keyboard->UpdateKeyboardState();
        mouse->UpdateMouseState();

        SDL_Event myEvent;
        while (SDL_PollEvent(&myEvent)) {
            switch (myEvent.type)
            {
                case SDL_QUIT:
                {
                    return;

                    break;
                }
                case SDL_WINDOWEVENT:
                {
                    break;
                }
                default:
                    break;
            }
        }

        if (mouse->LeftButtonClicked())
        {
            printf("LEFT CLICKED\n");
        }
        
        if (mouse->RightButtonPressed())
        {
            printf("Right Pressed\n");
        }

        if(keyboard->IsKeyClicked(Key::_Escape))
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

        mouse->UpdatePastMouseState();
    }
}

void GameEngine::PlayOne()
{
    SDL_Event myEvent;
    while (SDL_PollEvent(&myEvent)) {
        switch (myEvent.type)
        {
        case SDL_QUIT:
        {
            return;

            break;
        }
        case SDL_WINDOWEVENT:
        {
            break;
        }
        default:
            break;
        }
    }
}

void GameEngine::PlayOneUnlocked()
{
    SDL_Event myEvent;
    while (SDL_PollEvent(&myEvent)) {
        switch (myEvent.type)
        {
        case SDL_QUIT:
        {
            return;

            break;
        }
        case SDL_WINDOWEVENT:
        {
            break;
        }
        default:
            break;
        }
    }
}

ASprite* GameEngine::CreateSprite()
{
    LogTrace("GameEngine::CreateSprite");

    ASprite* sprt = AbstractFactory::CreateSprite(Renderer);

    return sprt;
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
    return currentFrameTime - previousFrameTime > 1000 / wantedFPS;
}

void GameEngine::Shutdown()
{
    LogTrace("GameEngine::Shutdown");

    SDL_Quit();
}
