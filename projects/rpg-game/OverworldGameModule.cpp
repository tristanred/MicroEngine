#include "OverworldGameModule.h"

#include "ConfigFile.h"

#include "microengine.h"

OverworldGameModule::OverworldGameModule(GameEngine* engine) : GameModule(engine)
{
    this->Map = this->CreateSprite();
    ATexture* mapTexture = this->CreateTexture("data/map.png");
    this->Map->SetTexture(mapTexture);

    this->PlayerCharacter = this->CreateSprite();
    ATexture* playerTexture = this->CreateTexture("data/player.png");
    this->PlayerCharacter->SetTexture(playerTexture);

}

OverworldGameModule::~OverworldGameModule()
{

}

void OverworldGameModule::Setup()
{

}

void OverworldGameModule::Update(unsigned int deltaTime)
{
    GameModule::Update(deltaTime);

    FPosition currentPlayerPos = this->PlayerCharacter->GetPosition();
    if (GetEngine()->Keyboard->IsKeyDown(Key::W))
    {
        currentPlayerPos.Y -= 3;
    }
    if (GetEngine()->Keyboard->IsKeyDown(Key::A))
    {
        currentPlayerPos.X -= 3;
    }
    if (GetEngine()->Keyboard->IsKeyDown(Key::S))
    {
        currentPlayerPos.Y += 3;
    }
    if (GetEngine()->Keyboard->IsKeyDown(Key::D))
    {
        currentPlayerPos.X += 3;
    }
    this->PlayerCharacter->SetPosition(currentPlayerPos);
}

void OverworldGameModule::Draw(ARenderer *renderer)
{
    renderer->Draw(this->Map);
    renderer->Draw(this->PlayerCharacter);
}
