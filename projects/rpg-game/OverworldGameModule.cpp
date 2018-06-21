#include "OverworldGameModule.h"

#include "ConfigFile.h"
#include "microengine.h"
#include "Framework/Tilemap.h"
#include "Viewport.h"

OverworldGameModule::OverworldGameModule(GameEngine* engine) : GameModule(engine)
{
    tiles = new Tilemap();
    tiles->Setup(20, 20, engine->Renderer);

    this->Map = this->CreateSprite();
    ATexture* mapTexture = this->CreateTexture("data/map.png");
    this->Map->SetTexture(mapTexture);

    this->PlayerCharacter = this->CreateSprite();
    ATexture* playerTexture = this->CreateTexture("data/player.png");
    this->PlayerCharacter->SetTexture(playerTexture);

    Viewport* view = this->CreateViewport();
    view->FollowSprite(this->PlayerCharacter);
    view->ViewRange = FRectangle(0, 0, 1000, 1000);

    this->GetEngine()->SelectViewport(view);
}

OverworldGameModule::~OverworldGameModule()
{

}

void OverworldGameModule::Update(unsigned int deltaTime)
{
    GameModule::Update(deltaTime);

    FPosition currentPlayerPos = this->PlayerCharacter->GetPosition();
    if (GetEngine()->Keyboard->IsKeyDown(Key::W))
    {
        currentPlayerPos.Y -= MOVE_SPEED;
    }
    if (GetEngine()->Keyboard->IsKeyDown(Key::A))
    {
        currentPlayerPos.X -= MOVE_SPEED;
    }
    if (GetEngine()->Keyboard->IsKeyDown(Key::S))
    {
        currentPlayerPos.Y += MOVE_SPEED;
    }
    if (GetEngine()->Keyboard->IsKeyDown(Key::D))
    {
        currentPlayerPos.X += MOVE_SPEED;
    }
    this->PlayerCharacter->SetPosition(currentPlayerPos);
}

void OverworldGameModule::Draw(ARenderer *renderer)
{
    //renderer->Draw(this->Map);
    tiles->Draw(renderer);

    renderer->Draw(this->PlayerCharacter);
}