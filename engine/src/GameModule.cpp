#include "GameModule.h"

#include <libtech/stdutils.h>

#include <algorithm>
#include <iterator>
#include <vector>

#include "GameEngine.h"
#include "Rendering/AFont.h"
#include "Rendering/ARenderer.h"
#include "Rendering/ASprite.h"
#include "Rendering/AText.h"
#include "TickTimer.h"
#include "Viewport.h"

GameModule::GameModule(GameEngine* engine)
{
    LogTrace("GameModule::GameModule");

    this->Engine = engine;
    Objects = new std::list<RenderableObject*>();

    Timers = new std::list<TickTimer*>();
}

GameModule::~GameModule()
{
    LogTrace("GameModule::~GameModule");

    // We do not clear the elements inside the list because they are
    // RenderableObjects and they are owned by the Engine.
    this->Objects->clear();
    delete(this->Objects);

    DELETE_LIST_ELEMENTS(this->Timers, TickTimer);
    delete(this->Timers);
}

void GameModule::Load()
{
    LogTrace("GameModule::Load");

    if(this->ModuleState == UNINITIALIZED)
    {
        this->ModuleState = LOADED;
    }
    else
    {
        LogWarning("GameModule::Load Invalid State %i", this->ModuleState);
    }
}

void GameModule::Activate()
{
    LogTrace("GameModule::Activate");

    if(this->ModuleState == LOADED)
    {
        this->ModuleState = ACTIVATED;
    }
    else
    {
        LogWarning("GameModule::Activate Invalid State %i", this->ModuleState);
    }
}

void GameModule::Stop()
{
    LogTrace("GameModule::Stop");

    if(this->ModuleState == ACTIVATED)
    {
        this->ModuleState = LOADED;
    }
    else
    {
        LogWarning("GameModule::Stop Invalid State %i", this->ModuleState);
    }
}

void GameModule::Unload()
{
    LogTrace("GameModule::Unload");

    if(this->ModuleState == LOADED)
    {
        this->ModuleState = UNINITIALIZED;
    }
    else
    {
        LogWarning("GameModule::Unload Invalid State %i", this->ModuleState);
    }
}

// ASprite* GameModule::CreateSprite()
// {
//     LogTrace("GameModule::CreateSprite");

//     ASprite* x = this->Engine->CreateSprite();

//     this->AttachRenderable(x);

//     return x;
// }

// ASprite* GameModule::CreateSprite(ATexture* texture)
// {
//     LogTrace("GameModule::CreateSprite");

//     ASprite* x = this->Engine->CreateSprite();
//     x->SetTexture(texture);

//     this->AttachRenderable(x);

//     return x;
// }

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

void GameModule::DestroyObject(RenderableObject* object)
{
    this->Objects->remove(object);

    this->Engine->ReleaseObject(object);
}

void GameModule::DestroyObject(ATexture* textureObject)
{
    this->Engine->ReleaseObject(textureObject);
}

Viewport* GameModule::CreateViewport()
{
    Viewport* vp = this->Engine->CreateViewport();

    return vp;
}

void GameModule::AttachRenderable(RenderableObject* object)
{
    LogTrace("GameModule::AttachRenderable");

    this->Objects->push_back(object);
}

void GameModule::Update(unsigned int deltaTime)
{
    this->UpdateTimers(deltaTime);
}

void GameModule::Draw(ARenderer* renderer)
{
    auto begin = this->Objects->begin();
    auto end = this->Objects->end();
    while(begin != end)
    {
        RenderableObject* obj = *begin;

        renderer->Draw(obj);

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
    while(begin != end)
    {
        TickTimer* timer = *begin;

        timer->Update(deltaTime);

        begin++;
    }
}
