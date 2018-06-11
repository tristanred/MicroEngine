#pragma once

// Engine classes
class ASprite;
class AText;
class Tilemap;

#include <GameModule.h>
#include <vector>
#include <list>
#include <string.h>
#include <string>

class OverworldGameModule : public GameModule
{
public:
    explicit OverworldGameModule(GameEngine* engine);
    ~OverworldGameModule() override;

    Tilemap* tiles;
    ASprite* Map;
    ASprite* PlayerCharacter;

    void Update(unsigned int deltaTime) override;
    void Draw(ARenderer *renderer) override;

private:
};
