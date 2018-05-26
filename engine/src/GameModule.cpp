#include "GameModule.h"

#include <SDL2/SDL.h>

#include "ARenderer.h"
#include "ASprite.h"
#include "SDL/SDLTexture.h"
#include "SDL/SDLSprite.h"
#include "GameEngine.h"


GameModule::GameModule(GameEngine* engine)
{
    this->Engine = engine;
    Objects = new std::list<ARenderable*>();
}

GameModule::~GameModule()
{
}

ASprite* GameModule::CreateSprite()
{
    auto x = new SDLSprite();

    SDLTexture* newT = new SDLTexture(this->Engine->Renderer);
    x->SetTexture(newT);
    this->Objects->push_back(x);

    return x;
}

void GameModule::Update()
{
}

void GameModule::Draw(ARenderer* renderer)
{
    auto begin = this->Objects->begin();
    auto end = this->Objects->end();
    while (begin != end)
    {
        ARenderable* obj = *begin;

        renderer->Draw(obj);

        begin++;
    }
}
