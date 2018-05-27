#include "GameEngine.h"

#include "ARenderer.h"
#include "SDL/SDLRenderer.h"
#include "GameModule.h"

#include <SDL2/SDL.h>

GameEngine::GameEngine()
{
    this->Modules = new std::list<GameModule *>();
}

GameEngine::~GameEngine()
{
}

void GameEngine::Start()
{
    Renderer = new SDLRenderer();

    Renderer->Initialize();
}

void GameEngine::Play()
{
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

        this->Draw();
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
    return nullptr;
}

void GameEngine::Update()
{

}

void GameEngine::Draw()
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
    auto test = new SDLTexture(this->Renderer);

    test->SetSize(FSize(100, 100));
    test->SetColor(0x88888888);


    return test;
}