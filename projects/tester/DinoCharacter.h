#pragma once

#include "Game/Game.h"

class DinoCharacter : GameObject
{
public:
    ASprite* DinoSprite;

    DinoCharacter();
    ~DinoCharacter();

    void Setup(GameModule* currentModule) override;
    void Update(unsigned int deltaTime) override;
    void Draw() override;
};
