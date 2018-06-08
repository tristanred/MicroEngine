#include "OverworldGameModule.h"

#include "ConfigFile.h"

OverworldGameModule::OverworldGameModule(GameEngine* engine) : GameModule(engine)
{
    CurrentMap = NULL;
}

OverworldGameModule::~OverworldGameModule()
{

}

void OverworldGameModule::Setup(std::string configFilePath)
{
    ConfigFile config = ConfigFile(configFilePath.c_str());

    

}

void OverworldGameModule::Update(unsigned int deltaTime)
{
    GameModule::Update(deltaTime);
}

void OverworldGameModule::Draw(ARenderer *renderer)
{
    GameModule::Draw(renderer);
}
