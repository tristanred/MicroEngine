#include "gameengine.h"

#include "renderer.h"

#include <SDL.h>

GameEngine::GameEngine()
{
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
