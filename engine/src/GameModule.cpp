#include "GameModule.h"

#include "ARenderer.h"
#include "ASprite.h"
#include "GameEngine.h"


GameModule::GameModule(GameEngine* engine)
{
    LogTrace("GameModule::GameModule");

    this->Engine = engine;
    Objects = new std::list<ARenderable*>();
}

GameModule::~GameModule()
{
    LogTrace("GameModule::~GameModule");
}

ASprite* GameModule::CreateSprite()
{
    LogTrace("GameModule::CreateSprite");

    ASprite* x = this->Engine->CreateSprite();

    this->AttachSprite(x);

    return x;
}

void GameModule::AttachSprite(ASprite* sprite)
{
    this->Objects->push_back(sprite);
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

ARenderer* GameModule::GetRenderer()
{
    return this->Engine->Renderer;
}

GameEngine* GameModule::GetEngine()
{
    return this->Engine;
}

