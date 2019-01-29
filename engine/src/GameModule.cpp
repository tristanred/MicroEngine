#include "GameModule.h"

#include <algorithm>
#include <vector>
#include <iterator>
#include <libtech/stdutils.h>

#include "ARenderer.h"
#include "ASprite.h"
#include "AText.h"
#include "AFont.h"
#include "GameEngine.h"
#include "Viewport.h"
#include "TickTimer.h"

GameModule::GameModule(GameEngine* engine)
{
    LogTrace("GameModule::GameModule");

    this->Engine = engine;
    Objects = new std::list<ARenderable*>();

    Timers = new std::list<TickTimer*>();
}

GameModule::~GameModule()
{
    LogTrace("GameModule::~GameModule");

    // We do not clear the elements inside the list because they are
    // ARenderables and they are owned by the Engine.
    this->Objects->clear();
    delete(this->Objects);

    DELETE_LIST_ELEMENTS(this->Timers, TickTimer);
    delete(this->Timers);
}

ASprite* GameModule::CreateSprite()
{
    LogTrace("GameModule::CreateSprite");

    ASprite* x = this->Engine->CreateSprite();

    this->AttachRenderable(x);

    return x;
}

ASprite* GameModule::CreateSprite(ATexture* texture)
{
    LogTrace("GameModule::CreateSprite");
    
    ASprite* x = this->Engine->CreateSprite();
    x->SetTexture(texture);
    
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

AText* GameModule::CreateText(AFont* textFont)
{
    LogTrace("GameModule::CreateText");
    
    AText* x = this->Engine->CreateText();
    x->SetFont(textFont);
    
    this->AttachRenderable(x);
    
    return x;
}

AFont* GameModule::CreateTextFont()
{
    LogTrace("GameModule::CreateTextFont");

    AFont* x = this->Engine->CreateTextFont();

    return x;
}

ATexture* GameModule::CreateTexture()
{
    ATexture* texture = this->Engine->CreateTexture();

    return texture;
}

ATexture* GameModule::CreateTexture(const char* textureName)
{
    ATexture* texture = this->Engine->CreateTexture(textureName);

    return texture;
}

void GameModule::DestroyObject(ARenderable* object)
{
    this->Engine->ReleaseObject(object);
}

Viewport* GameModule::CreateViewport()
{
    Viewport* vp = this->Engine->CreateViewport();

    return vp;
}

void GameModule::AttachRenderable(ARenderable* object)
{
    LogTrace("GameModule::AttachRenderable");

    this->Objects->push_back(object);
}

void GameModule::Enabled()
{
    moduleEnabled = true;
}

void GameModule::Disabled()
{
    moduleEnabled = false;
}

void GameModule::Update(unsigned int deltaTime)
{
    this->UpdateTimers(deltaTime);
}

void GameModule::Draw(ARenderer* renderer)
{
    auto begin = this->Objects->begin();
    auto end = this->Objects->end();
    while (begin != end)
    {
        ARenderable* obj = *begin;

        if(obj->GetParent() == NULL)
        {
            renderer->Draw(obj);
        }

        if(obj->GetChildren()->Count() > 0)
        {
            for(int i = 0; i < obj->GetChildren()->Count(); i++)
            {
                renderer->Draw(obj->GetChildren()->Get(i));
            }
        }

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

TickTimer* GameModule::CreateTimer(uint32_t totalTime)
{
    TickTimer* newTimer = new TickTimer(totalTime);

    this->Timers->push_back(newTimer);

    return newTimer;
}

void GameModule::DestroyTimer(TickTimer* timer)
{
    auto iter = std::find(Timers->begin(), Timers->end(), timer);

    if(iter != Timers->end())
    {
        TickTimer* result = *iter;

        std::remove(Timers->begin(), Timers->end(), timer);

        delete(result);
    }
}

void GameModule::UpdateTimers(uint32_t deltaTime)
{
    auto begin = this->Timers->begin();
    auto end = this->Timers->end();
    while (begin != end)
    {
        TickTimer* timer = *begin;

        timer->Update(deltaTime);

        begin++;
    }
}
