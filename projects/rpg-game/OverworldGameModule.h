#pragma once

// Engine classes
class ASprite;
class AText;

#include <GameModule.h>

// Game Classes
class GameMap;

#include <vector>
#include <list>
#include <string.h>
#include <string>

class OverworldGameModule : public GameModule
{
public:
    explicit OverworldGameModule(GameEngine* engine);
    ~OverworldGameModule() override;

    GameMap* CurrentMap;
    std::list<GameMap*> Maps;

    void Setup(std::string configFilePath);

    void Update(unsigned int deltaTime) override;
    void Draw(ARenderer *renderer) override;

private:
};
