#pragma once

#include <Controls/CButton.h>
#include <Game/Tilemap.h>
#include <GameEngine.h>
#include <GameModule.h>
#include <Rendering/AFont.h>
#include <Rendering/ARenderer.h>
#include <Rendering/ASprite.h>
#include <Rendering/AText.h>
#include <Rendering/ATexture.h>
#include <TickTimer.h>
#include <libtech/vec.h>
#include <stdint.h>

#include "DinoCharacter.h"

class GameTestModule : public GameModule
{
public:
    GameTestModule(GameEngine* engine);
    ~GameTestModule();

    ASprite* Box;
    ASprite* Box2;
    ATexture* BoxTexture;
    AText* BoxText;
    AFont* ArialFont;
    vec2 boxVelocity;

    CButton* buttan;

    ASprite* clockSprite;

    DinoCharacter* Dinono;

    AText* TimerText;
    TickTimer* timer;

    Tilemap* Map;

    void Update(unsigned int deltaTime) override;
};
