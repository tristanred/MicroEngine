#include "GameModule.h"

#include "ARenderer.h"
#include "ASprite.h"
#include "AText.h"
#include "AFont.h"
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

    this->AttachRenderable(x);

    return x;
}

AText* GameModule::CreateText()
{
    LogTrace("GameModule::CreateText");

    AText* x = this->Engine->CreateText();

    this->AttachRenderable(x);

    return x;
}

AFont* GameModule::CreateFont()
{
    LogTrace("GameModule::CreateFont");

    AFont* x = this->Engine->CreateFont();

    return x;
}

ATexture* GameModule::CreateTexture()
{
    ATexture* texture = this->Engine->CreateTexture();

    return texture;
}

ATexture* GameModule::CreateTexture(const char* filePath)
{
    ATexture* texture = this->Engine->CreateTexture(filePath);

    return texture;
}

void GameModule::AttachRenderable(ARenderable* object)
{
    LogTrace("GameModule::AttachRenderable");

    this->Objects->push_back(object);
}

void GameModule::Update(unsigned int deltaTime)
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

