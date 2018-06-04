#include "OverworldGameModule.h"

OverworldGameModule::OverworldGameModule(GameEngine* engine) : GameModule(engine)
{

}

OverworldGameModule::~OverworldGameModule()
{

}

void OverworldGameModule::Update()
{
    GameModule::Update();
}

void OverworldGameModule::Draw(ARenderer *renderer)
{
    GameModule::Draw(renderer);
}
