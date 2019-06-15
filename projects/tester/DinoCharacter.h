#pragma once

#include "Game/Game.h"

class DinoCharacter : GameObject
{
public:
    ASprite* DinoSprite;

    DinoCharacter(GameEngine* engine);
    ~DinoCharacter();

    void Setup(GameModule* currentModule);
    void Update(unsigned int deltaTime) override;
};
