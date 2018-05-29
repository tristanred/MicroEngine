#include "GameEngine.h"

#include "ARenderer.h"
#include "GameModule.h"
#include "libtech/filelogger.h"
#include "TextureRepository.h"
#include "AbstractFactory.h"

#include <SDL.h>

GameEngine::GameEngine()
{
    this->Modules = new std::list<GameModule *>();

    GameLog = new FileLogger();
    GameLog->Open("gamelog.txt");
    GameLog->LogMessage("Game Log Initialized");
    RegisterLogger(GameLog);
    LogTrace("GameEngine::GameEngine");
}

GameEngine::~GameEngine()
{
    LogTrace("GameEngine::~GameEngine");

    GameLog->Close();
}

void GameEngine::Start()
{
    LogTrace("GameEngine::Start");

    Renderer = AbstractFactory::CreateRenderer();

    Renderer->Initialize();

    TextureRepo = new TextureRepository(Renderer);
}

void GameEngine::Play()
{
    LogTrace("GameEngine::Play");

    while (true)
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

        Renderer->BeginDraw();

        this->DrawModules();

        Renderer->EndDraw();
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

    ASprite* sprt = AbstractFactory::CreateSprite();

    return sprt;
}

void GameEngine::Update()
{

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
    auto test = AbstractFactory::CreateTexture(this->Renderer);

    test->SetSize(FSize(100, 100));
    test->SetColor(0xFFFF0000);

    return test;
}
